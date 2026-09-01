#!/usr/bin/env bash
set -euo pipefail

validator=${1:-./validate_yaml_file}

expect_failure() {
  local fixture=$1
  shift

  local output
  if output=$("$validator" --repository "tests/fixtures/$fixture" 2>&1); then
    echo "expected $fixture to fail" >&2
    exit 1
  fi

  for expected in "$@"; do
    if [[ $output != *"$expected"* ]]; then
      echo "expected $fixture diagnostic to contain: $expected" >&2
      echo "$output" >&2
      exit 1
    fi
  done
}

"$validator" --repository tests/fixtures/valid-inline-support

expect_failure invalid-frontend-version \
  features_cpp26.yaml \
  "Undeclared frontend release" \
  "Version validation" \
  "R++ 2026.3"

expect_failure invalid-missing-tracker \
  features_cpp26.yaml \
  "does not define an issue tracker" \
  "Tracker validation" \
  "R++ 2026.2"

expect_failure invalid-unknown-tool \
  features_cpp26.yaml \
  "Unknown support tool" \
  "Unknown tool validation" \
  "Preview 1"

expect_failure invalid-compact-modifier \
  features_cpp26.yaml \
  "Invalid support suffix" \
  "Modifier validation" \
  "GCC 15 (hint)"

expect_failure invalid-object-shape \
  features_cpp26.yaml \
  "Structured support has no separate version field" \
  "GCC"

"$validator" --repository tests/fixtures/root-local-schema
