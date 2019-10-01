# Tests the basic runs


# Sanity checks
if [[ -z "$ROOT_TESTS" || -z "$BIN_WE" ]]; then
  echo
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS or BIN_WE not set"
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS: [$ROOT_TESTS] "
  exit 2
fi


pushd "$ROOT_PROJECT" > /dev/null
  timeout 3 "$BIN_WE"
  if [ $? -eq 124 ]; then
    return 0
  fi
  return 1
popd > /dev/null
