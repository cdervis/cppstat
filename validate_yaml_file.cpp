// Copyright (c) Cem Dervis
// SPDX-License-Identifier: CC0-1.0
// This file is part of https://cppstat.dev.

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>
#include <yaml-cpp/yaml.h>

using json = nlohmann::json;
namespace fs = std::filesystem;

struct frontend_definition
{
  std::string name;
  std::unordered_set<std::string> releases;
  bool has_issue_tracker = false;
};

namespace
{
struct support_tool_definition
{
  std::string name;
  const frontend_definition *frontend = nullptr;
  bool has_issue_tracker = false;
};

json yaml_to_json(const YAML::Node &node)
{
  if (node.IsNull())
  {
    return nullptr;
  }

  if (node.IsScalar())
  {
    if (node.Tag() == "!")
    {
      return node.as<std::string>();
    }

    try
    {
      return node.as<bool>();
    }
    catch (...)
    {
    }

    try
    {
      return node.as<int64_t>();
    }
    catch (...)
    {
    }

    try
    {
      return node.as<double>();
    }
    catch (...)
    {
    }

    return node.as<std::string>();
  }

  if (node.IsSequence())
  {
    auto arr = json::array();

    for (const auto &item : node)
    {
      arr.push_back(yaml_to_json(item));
    }

    return arr;
  }

  if (node.IsMap())
  {
    auto obj = json::object();

    for (const auto &kv : node)
    {
      obj[kv.first.as<std::string>()] = yaml_to_json(kv.second);
    }

    return obj;
  }

  return nullptr;
}

auto matching_files(const fs::path &root, std::string_view prefix, std::string_view suffix)
    -> std::vector<fs::path>
{
  auto files = std::vector<fs::path>();

  for (const auto &entry : fs::directory_iterator(root))
  {
    if (!entry.is_regular_file())
    {
      continue;
    }

    const auto filename = entry.path().filename().string();

    if (filename.starts_with(prefix) && filename.ends_with(suffix))
    {
      files.push_back(entry.path());
    }
  }

  std::ranges::sort(files);
  return files;
}

auto schema_error_support_indexes(std::string_view message) -> std::optional<std::pair<size_t, size_t>>
{
  constexpr auto prefix = std::string_view("At /features/");
  auto position = message.find(prefix);

  if (position == std::string_view::npos)
  {
    return std::nullopt;
  }

  position += prefix.size();

  const auto parse_index = [&](size_t &cursor) -> std::optional<size_t> {
    if (cursor >= message.size() || message[cursor] < '0' || message[cursor] > '9')
    {
      return std::nullopt;
    }

    auto value = size_t(0);

    while (cursor < message.size() && message[cursor] >= '0' && message[cursor] <= '9')
    {
      value = value * 10 + static_cast<size_t>(message[cursor] - '0');
      ++cursor;
    }

    return value;
  };

  const auto feature_index = parse_index(position);
  constexpr auto separator = std::string_view("/support/");

  if (!feature_index.has_value() || message.substr(position, separator.size()) != separator)
  {
    return std::nullopt;
  }

  position += separator.size();

  const auto support_index = parse_index(position);

  if (!support_index.has_value())
  {
    return std::nullopt;
  }

  return std::pair(*feature_index, *support_index);
}

auto contextual_schema_error(const fs::path &data_path, std::string_view message) -> std::string
{
  const auto indexes = schema_error_support_indexes(message);

  if (!indexes.has_value())
  {
    return std::format("{}: {}", data_path.filename().string(), message);
  }

  const auto document = YAML::LoadFile(data_path.string());
  const auto features = document["features"];

  if (!features || !features.IsSequence() || indexes->first >= features.size())
  {
    return std::format("{}: {}", data_path.filename().string(), message);
  }

  const auto feature = features[indexes->first];
  const auto support = feature["support"];

  if (!support || !support.IsSequence() || indexes->second >= support.size())
  {
    return std::format("{}: {}", data_path.filename().string(), message);
  }

  const auto entry = support[indexes->second];
  const auto value = entry.IsMap() && entry["tool"] && entry["tool"].IsScalar()
                         ? entry["tool"].as<std::string>()
                     : entry.IsScalar() ? entry.as<std::string>()
                                        : yaml_to_json(entry).dump();
  return std::format("{}: feature \"{}\": support \"{}\": {}", data_path.filename().string(),
                     feature["desc"].as<std::string>(), value, message);
}

void validate_file(const fs::path &data_path, const fs::path &schema_path)
{
  const auto schema = yaml_to_json(YAML::LoadFile(schema_path.string()));
  const auto data = yaml_to_json(YAML::LoadFile(data_path.string()));

  auto validator = nlohmann::json_schema::json_validator();
  validator.set_root_schema(schema);

  try
  {
    validator.validate(data);
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error(contextual_schema_error(data_path, e.what()));
  }
}

auto schema_path_for(const fs::path &root, std::string_view filename) -> fs::path
{
  const auto repository_path = root / filename;

  if (fs::exists(repository_path))
  {
    return repository_path;
  }

  return fs::current_path() / filename;
}

bool starts_with_registered_name(std::string_view value, const std::vector<std::string> &names)
{
  return std::ranges::any_of(names, [&](const std::string &name) {
    return value.starts_with(name) && value.size() > name.size() && value[name.size()] == ' ';
  });
}

auto load_toolchain_names(const fs::path &root) -> std::vector<std::string>
{
  auto names = std::vector<std::string>();

  for (const auto &path : matching_files(root, "toolchain_", ".yaml"))
  {
    const auto document = YAML::LoadFile(path.string());
    const auto infos = document["infos"];

    if (!infos || !infos.IsSequence() || infos.size() == 0)
    {
      throw std::runtime_error(std::format("{}: expected a non-empty infos list", path.filename().string()));
    }

    auto file_names = std::vector<std::string>();

    for (const auto &info : infos)
    {
      if (!info["name"] || !info["name"].IsScalar())
      {
        throw std::runtime_error(std::format("{}: infos entry has no name", path.filename().string()));
      }

      auto name = info["name"].as<std::string>();

      if (starts_with_registered_name(name, file_names))
      {
        break;
      }

      file_names.push_back(std::move(name));
    }

    names.insert(names.end(), file_names.begin(), file_names.end());
  }

  return names;
}

auto support_error(const fs::path &path, std::string_view description, std::string_view raw_tool,
                   std::string_view reason) -> std::runtime_error
{
  return std::runtime_error(std::format("{}: feature \"{}\": support \"{}\": {}", path.filename().string(),
                                        description, raw_tool, reason));
}

auto resolve_support(const fs::path &path, std::string_view description, const std::string &raw_tool,
                     const bool compact, const std::vector<support_tool_definition> &definitions)
    -> const support_tool_definition *
{
  for (const auto &definition : definitions)
  {
    if (raw_tool != definition.name &&
        !(raw_tool.starts_with(definition.name) && raw_tool.size() > definition.name.size() &&
          raw_tool[definition.name.size()] == ' '))
    {
      continue;
    }

    auto suffix = raw_tool.substr(definition.name.size());

    if (!suffix.empty())
    {
      suffix.erase(0, 1);
    }

    if (compact && suffix.ends_with(" (partial)"))
    {
      suffix.erase(suffix.size() - std::string_view(" (partial)").size());
    }
    else if (compact && suffix == "(partial)")
    {
      suffix.clear();
    }

    if (!suffix.empty() && suffix.find_first_of(" \t\r\n()") != std::string::npos)
    {
      throw support_error(path, description, raw_tool, "Invalid support suffix");
    }

    if (definition.frontend != nullptr && !suffix.empty() && !definition.frontend->releases.contains(suffix))
    {
      throw support_error(path, description, raw_tool, "Undeclared frontend release");
    }

    return &definition;
  }

  throw support_error(path, description, raw_tool, "Unknown support tool");
}

void validate_feature_semantics(const fs::path &path, const std::vector<support_tool_definition> &definitions)
{
  const auto document = YAML::LoadFile(path.string());

  for (const auto &feature : document["features"])
  {
    const auto description = feature["desc"].as<std::string>();
    const auto support = feature["support"];

    if (!support)
    {
      continue;
    }

    for (const auto &entry : support)
    {
      const auto compact = entry.IsScalar();
      const auto raw_tool = compact ? entry.as<std::string>() : entry["tool"].as<std::string>();
      const auto tool = resolve_support(path, description, raw_tool, compact, definitions);

      if (!compact && entry["issue"] && !tool->has_issue_tracker)
      {
        throw support_error(path, description, raw_tool, "Resolved tool does not define an issue tracker");
      }
    }
  }
}

} // namespace

auto load_frontend_definitions(const fs::path &root) -> std::vector<frontend_definition>
{
  auto definitions = std::vector<frontend_definition>();

  for (const auto &path : matching_files(root, "frontend_", ".yaml"))
  {
    const auto document = YAML::LoadFile(path.string());
    auto definition = frontend_definition();
    definition.name = document["frontend"]["name"].as<std::string>();
    definition.has_issue_tracker = static_cast<bool>(document["issue_tracker"]);

    for (const auto &release : document["releases"])
    {
      definition.releases.insert(release["version"].as<std::string>());
    }

    definitions.push_back(std::move(definition));
  }

  return definitions;
}

void validate_repository(const fs::path &root)
{
  if (!fs::is_directory(root))
  {
    throw std::runtime_error(std::format("Not a repository directory: {}", root.string()));
  }

  const auto feature_schema = schema_path_for(root, "features.schema.yaml");
  const auto frontend_schema = schema_path_for(root, "frontend.schema.yaml");
  const auto feature_files = matching_files(root, "features_", ".yaml");
  const auto frontend_files = matching_files(root, "frontend_", ".yaml");

  for (const auto &path : feature_files)
  {
    validate_file(path, feature_schema);
  }

  for (const auto &path : frontend_files)
  {
    validate_file(path, frontend_schema);
  }

  auto frontends = load_frontend_definitions(root);
  auto definitions = std::vector<support_tool_definition>();

  for (auto &name : load_toolchain_names(root))
  {
    definitions.push_back({std::move(name), nullptr, false});
  }

  for (const auto &frontend : frontends)
  {
    definitions.push_back({frontend.name, &frontend, frontend.has_issue_tracker});
  }

  std::ranges::sort(definitions,
                    [](const auto &lhs, const auto &rhs) { return lhs.name.size() > rhs.name.size(); });

  for (const auto &path : feature_files)
  {
    validate_feature_semantics(path, definitions);
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2 || argc > 3)
  {
    std::println(stderr, "Usage: {} <data_file.yaml> [schema.yaml]", argv[0]);
    std::println(stderr, "       {} --repository <root>", argv[0]);
    return EXIT_FAILURE;
  }

  const auto is_repository = std::string_view(argv[1]) == "--repository";

  try
  {
    if (is_repository)
    {
      if (argc != 3)
      {
        throw std::runtime_error("--repository requires a root directory");
      }

      validate_repository(argv[2]);
      std::println("Repository verification successful: {}", argv[2]);

      return EXIT_SUCCESS;
    }

    const auto schema_path = argc == 3 ? fs::path(argv[2]) : fs::path("features.schema.yaml");
    validate_file(argv[1], schema_path);
    std::println("Verification successful: {}", argv[1]);

    return EXIT_SUCCESS;
  }
  catch (const std::exception &e)
  {
    const auto subject = argc == 3 && is_repository ? argv[2] : argv[1];

    std::println(stderr, "Verification failed: {}", subject);
    std::println(stderr, "Error: {}", e.what());

    return EXIT_FAILURE;
  }
}
