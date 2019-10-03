#!/bin/bash


. "${ROOT_TESTS}/utils/log.sh"


# autoreconf && configure
function _configure()
{
  beginSection "CONFIGURE"

  pushd "${ROOT_PROJECT}"
    autoreconf --force --install --warnings=all
    local ret_code=$?
    if [[ $ret_code -ne 0 ]]; then
      printError "Autoreconf returned $ret_code"
      exit $ret_code
    fi
  popd # $ROOT_PROJECT

  pushd "$BUILD_DIR"
    "${ROOT_PROJECT}/configure" --prefix="${ROOT_TESTS}"
    ret_code=$?
    if [[ $ret_code -ne 0 ]]; then
      printError "Unable to configure"
      exit $ret_code
    fi
  popd # $BUILD_DIR

  endSection
}



# compilation appending -Werror and installing
function _standard_compilation()
{
  beginSection "BUILD"

  make -C "$BUILD_DIR" WE_EXTRA_CXXFLAGS=-Werror all install
  local ret_code=$?
  if [[ $ret_code -ne 0 ]]; then
    printError "Compilation error"
    exit $ret_code
  fi

  endSection
}



function build_main()
{
  rm -rf bin/ "$BUILD_DIR"
  mkdir -p "$BUILD_DIR"

  _configure && _standard_compilation
}
