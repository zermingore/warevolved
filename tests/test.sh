#!/bin/bash


ROOT_TESTS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"
ROOT_PROJECT="${ROOT_TESTS}/.."
BUILD_DIR=build


rm -rf bin/ "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

. utils/build.sh

build
