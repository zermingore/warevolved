#!/bin/bash

set -o pipefail


ROOT_TESTS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"
ROOT_PROJECT="${ROOT_TESTS}/.."
BUILD_DIR=build

. utils/log.sh


rm -rf bin/ "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

. utils/build.sh

build

BIN_WE=${ROOT_TESTS}/$(find . -name we -type f -executable)
if [ -z "$BIN_WE" ]; then
  printError "Binary not found"
  exit 2
fi



# Smoke Tests
find smoke -type f -iname "*.sh" -print0 \
  | while IFS= read -r -d $'\0' file
do
  echo -n "Testing ${file}... "
  . "$file"
  if [[ $? -ne 0 ]]; then # Aborting whatever the failure in a smoke test is
    printError "Smoke tests failed; Aborting..."
    exit 1
  fi

  printSuccess "[done]"
done



# TODO main
