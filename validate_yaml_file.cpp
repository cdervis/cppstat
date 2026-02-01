// Copyright (c) Cem Dervis
// SPDX-License-Identifier: CC0-1.0
// This file is part of https://cppstat.dev.

#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>
#include <print>
#include <yaml-cpp/yaml.h>

using json = nlohmann::json;

json yaml_to_json(const YAML::Node& node) {
  if (node.IsNull()) {
    return nullptr;
  }
  else if (node.IsScalar()) {
    try {
      return node.as<bool>();
    } catch (...) {
    }

    try {
      return node.as<int64_t>();
    } catch (...) {
    }

    try {
      return node.as<double>();
    } catch (...) {
    }

    return node.as<std::string>();
  }
  else if (node.IsSequence()) {
    auto arr = json::array();

    for (const auto& item : node) {
      arr.push_back(yaml_to_json(item));
    }

    return arr;
  }
  else if (node.IsMap()) {
    auto obj = json::object();

    for (const auto& kv : node) {
      obj[kv.first.as<std::string>()] = yaml_to_json(kv.second);
    }

    return obj;
  }

  return nullptr;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::println(stderr, "Usage: {} <data_file.yaml>", argv[0]);
    return EXIT_FAILURE;
  }

  try {
    auto schema_yaml = YAML::LoadFile("features.schema.yaml");
    auto schema      = yaml_to_json(schema_yaml);

    auto data_yaml = YAML::LoadFile(argv[1]);
    auto data      = yaml_to_json(data_yaml);

    auto val = nlohmann::json_schema::json_validator();
    val.set_root_schema(schema);
    val.validate(data);

    std::println("Verification successful: {}", argv[1]);

    return EXIT_SUCCESS;
  } catch (const std::exception& e) {
    std::println(stderr, "Verification failed: {}", argv[1]);
    std::println(stderr, "Error: {}", e.what());
    return EXIT_FAILURE;
  }
}
