#!/bin/bash

set -E
trap '[ "$?" -eq 123 ] && exit 123' ERR


# NOTE: modern getopt and bash-compliant shell required

set -o pipefail


VERSION=0.1.0

# Program options
OPTIONS=hjnrsvi
OPTIONS_LONG=\
help,\
version,\
safe-mode,\
no-configure,\
parallel-build,\
no-configure,\
random-seed:,\
smoke,\
regression,\
integration,\
tests:


# Program options associated variables
PARALLEL_BUILD="-j1"
NO_CONFIGURE=0
RUN_ALL_TYPES=1
RUN_SMOKE=0
RUN_REGRESSION=0
RUN_INTEGRATION=0
RANDOM_SEED=$(shuf -i 0-4294967296 -n 1)
SAFE_MODE=0


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
    set -x
    . "$file"
    local ret=$?
    set +x
    if [[ $ret -ne 0 ]]; then # Aborting whatever the failure is
      printError "[FAIL]\n  Smoke tests failed; Aborting..."
      exit 123
    fi

    printSuccess "[done]\n"
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
    set -x
    . "$file"
    local ret=$?
    set +x
    if [[ $ret -ne 0 ]]; then
      printError "[FAIL]\n"
      ret_val=1
    else
      printSuccess "[done]\n"
    fi
  done

  endSection
  return $ret_val
}



function integration_tests()
{
  local ret_val=0
  beginSection "INTEGRATION TESTS"

  for file in $(find "${ROOT_TESTS}/integration" -type f -iname "*.sh")
  do
    echo -n "Testing ${file}... "
    set -x
    . "$file"
    local ret=$?
    set +x
    if [[ $ret -ne 0 ]]; then
      printError "[FAIL]"
      ret_val=1
    else
      printSuccess "[done]\n"
    fi
  done

  endSection
  return $ret_val
}



function safe_mode()
{
  local -r tmp_dir=$(mktemp -d)

  echo -n "Copying tracked files in ${tmp_dir}... "
  for f in $(git ls-files); do
    cp --parents "$f" "$tmp_dir"
    if [[ $? -ne 0 ]]; then
      printError "[FAIL]"
      exit 3
    fi
  done
  printSuccess "[done]\n"

  pushd "$tmp_dir" >/dev/null
  if [ $? -ne 0 ]; then
    printError "Cannot cd to temp directory $tmp_dir"
    exit 3
  fi

  tests/test.sh
}


# ________________________________ Entry point _______________________________ #
function main()
{
  parse_options "$@"

  if [ $SAFE_MODE -eq 1 ]; then
    if [ $# -ne 1 ]; then
      printError "--safe-mode is not compatible with any option"
      exit 2
    fi

    safe_mode
    exit $?
  fi

  build
  # Get the absolute path to the 'we' binary
  BIN_WE=$(find "${ROOT_TESTS}" -name we -type f -executable \
                -exec readlink -f {} \;)
  if [ -z "$BIN_WE" ]; then
    printError "Binary not found"
    exit 2
  fi


  local result=0
  echo "Using random seed: $RANDOM_SEED"

  # Smoke tests
  if [[ $RUN_ALL_TYPES -eq 1 || $RUN_SMOKE -eq 1 ]]; then
    smoke_tests
  fi

  # Regression tests
  if [[ $RUN_ALL_TYPES -eq 1 || $RUN_REGRESSION -eq 1 ]]; then
    non_regression_tests
    if [[ $? -ne 0 ]]; then
      result=1
    fi
  fi

  # Integration tests
  if [[ $RUN_ALL_TYPES -eq 1 || $RUN_INTEGRATION -eq 1 ]]; then
    integration_tests
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
