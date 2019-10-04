#!/bin/bash

# NOTE: modern getopt and bash-compliant shell required


set -o pipefail


VERSION=0.1.0

# Program options
OPTIONS=hjnrsv
OPTIONS_LONG=\
help,\
no-configure,\
parallel-build,\
no-configure,\
regression,\
smoke,\
tests:,\
version

# Program options associated variables
PARALLEL_BUILD="-j1"
NO_CONFIGURE=0
RUN_ALL_TYPES=1
RUN_REGRESSION=0
RUN_SMOKE=0


# Paths
ROOT_TESTS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"
ROOT_PROJECT="${ROOT_TESTS}/.."
BUILD_DIR=build


. "${ROOT_TESTS}/utils/log.sh"
. "${ROOT_TESTS}/utils/options_parser.sh"
. "${ROOT_TESTS}/utils/build.sh"


function build()
{
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
  done

  endSection
  return $ret_val
}



# ________________________________ Entry point _______________________________ #
function main()
{
  parse_options "$@"

  local result=0

  build

  # Get the absolute path to the 'we' binary
  BIN_WE=$(find "${ROOT_TESTS}" -name we -type f -executable \
                -exec readlink -f {} \;)
  if [ -z "$BIN_WE" ]; then
    printError "Binary not found"
    exit 2
  fi

  # Smoke tests
  if [[ $RUN_ALL_TYPES -eq 1 || $RUN_SMOKE -eq 1 ]]; then
    smoke_tests || exit $?
  fi

  # Regression tests
  if [[ $RUN_ALL_TYPES -eq 1 || $RUN_REGRESSION -eq 1 ]]; then
    non_regression_tests
    if [[ $? -ne 0 ]]; then
      result=1
    fi
  fi

  # Handle --tests=list
  for test_file in "${TESTS_LIST[@]}"
  do
    echo -n "Testing ${test_file}... "
    . $test_file
    if [[ $? -ne 0 ]]; then
      printError "[FAIL]"
      result=1
    else
      printSuccess "[done]\n"
    fi
  done

  exit $result
}

main "$@"
