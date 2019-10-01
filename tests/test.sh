#!/bin/bash

set -o pipefail


ROOT_TESTS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"
ROOT_PROJECT="${ROOT_TESTS}/.."
BUILD_DIR=build

. "${ROOT_TESTS}/utils/log.sh"



function build()
{
  rm -rf bin/ "$BUILD_DIR"
  mkdir -p "$BUILD_DIR"

  . "${ROOT_TESTS}/utils/build.sh"
  build_main
}



function smoke_tests()
{
  beginSection "SMOKE TESTS"

  find "${ROOT_TESTS}/smoke" -type f -iname "*.sh" -print0 \
    | while IFS= read -r -d $'\0' file
  do
    echo -n "Testing ${file}... "
    . "$file"
    if [[ $? -ne 0 ]]; then # Aborting whatever the failure in a smoke test is
      printError "[FAIL]\n  Smoke tests failed; Aborting..."
      exit 1
    fi

    printSuccess "[done]"
  done

  endSection
}



function non_regression_tests()
{
  local ret_val=0
  beginSection "NON REGRESSION TESTS"

  for file in $(find "${ROOT_TESTS}/regression" -type f -iname "*.sh")
  do
    echo -n "Testing ${file}... "
    . "$file"
    if [[ $? -ne 0 ]]; then
      printError "[FAIL]"
      ret_val=1
    else
      printSuccess "[done]\n"
    fi
    ret_val=1
  done

  endSection
  return $ret_val
}



# ________________________________ Entry point _______________________________ #
function main()
{
  result=0

  build

  # Get the absolute path to the 'we' binary
  BIN_WE=$(find "${ROOT_TESTS}" -name we -type f -executable \
                -exec readlink -f {} \;)
  if [ -z "$BIN_WE" ]; then
    printError "Binary not found"
    exit 2
  fi

  smoke_tests || exit $?
  non_regression_tests
  if [[ $? -ne 0 ]]; then
    result=1
  fi

  exit $result
}

main
