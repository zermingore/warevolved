#!/bin/bash


# Sanity checks
if [[ -z "$ROOT_TESTS" || -z "$BIN_WE" ]]; then
  echo
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS or BIN_WE not set"
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS: [$ROOT_TESTS] "
  exit 2
fi


pushd "$ROOT_PROJECT" > /dev/null
  "$BIN_WE" --help > /dev/null || return 1
  "$BIN_WE" --version > /dev/null || return 1
  "$BIN_WE" --not-an-option > /dev/null 2>&1 && return 1
  "$BIN_WE" --load-map=this_map_does_not_exist > /dev/null 2>&1 && return 1;
  "$BIN_WE" --saves-directory=/not_writable > /dev/null 2>&1 && return 1;
popd > /dev/null
