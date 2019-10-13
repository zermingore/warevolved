#!/bin/bash

# Check if the headers can be compiled separately.
# Compiles the headers


# Compiler and Flags
CXX=g++
CXXFLAGS="-O0 -DDEBUG -DDEBUG_LEAKS \
 -Wall -Wextra -Wpedantic -Waggressive-loop-optimizations -Wformat=2 \
 -Wformat-contains-nul -Wformat-extra-args -Wformat-signedness \
 -Wformat-zero-length -Warray-bounds=2 -Wattributes -Wbool-compare \
 -Wbuiltin-macro-redefined -Wcast-align -Wcast-qual \
 -Wconditionally-supported -Wconversion -Wconversion-null -Wctor-dtor-privacy \
 -Wdate-time -Wdelete-incomplete -Wdeprecated -Wdeprecated-declarations \
 -Wdisabled-optimization -Wdiv-by-zero -Wdouble-promotion -Wendif-labels \
 -Wfloat-equal -Wfree-nonheap-object -Winherited-variadic-ctor -Winit-self \
 -Winline -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-offsetof \
 -Winvalid-pch -Wlarger-than=4096 -Wliteral-suffix -Wlogical-not-parentheses \
 -Wlogical-op -Wlong-long -Wmemset-transposed-args -Wmissing-declarations \
 -Wmissing-include-dirs -Wnoexcept -Wnon-template-friend -Wnon-virtual-dtor \
 -Wnormalized -Wodr -Wold-style-cast -Woverflow -Woverloaded-virtual -Wpacked \
 -Wpacked-bitfield-compat -Wpmf-conversions -Wpragmas -Wredundant-decls \
 -Wreturn-local-addr -Wshadow -Wshift-count-negative -Wshift-count-overflow \
 -Wsign-promo -Wsized-deallocation -Wsizeof-array-argument \
 -Wsizeof-pointer-memaccess -Wstack-protector -Wstrict-null-sentinel \
 -Wstrict-overflow=5 -Wsuggest-attribute=const -Wsuggest-attribute=format \
 -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods \
 -Wsuggest-final-types -Wsuggest-override -Wswitch-bool -Wswitch-default \
 -Wsync-nand -Wtrampolines -Wunsafe-loop-optimizations \
 -Wuseless-cast -Wvarargs -Wvector-operation-performance -Wvirtual-move-assign \
 -Wwrite-strings -Wzero-as-null-pointer-constant -std=c++2a -pthread"
# removed -Wunused-macros to hide warnings about unused header guard


# Colors for fancy prints
COLOR_RED=$(echo -e '\e[0;31m')
COLOR_GREEN=$(echo -e '\e[0;32m')
COLOR_NORMAL=$(echo -e '\e[0m')
# COLOR_YELLOW=$(echo -e '\e[0;33m')

TMP_SRC=/tmp/check_headers
CXXINCLUDES="-I$1 -I$1/../lib/" # -I.
COMPILE="$CXX $CXXINCLUDES $CXXFLAGS -o ${TMP_SRC}/unused_header"



function usage()
{
  echo -e "\n\t./$(basename "$0") path_to_project_root"
}



function version()
{
  echo -e "$(basename "$0") Version 1.0.0"
}



function help()
{
  echo
  echo "Check if the headers are self sufficient in a project"
  echo "The project must have a main.cc"
  echo
  echo "  -h --help    display this help"
  echo "  -v --version display the program version"
  echo
  echo "                              Written for War Evolved"
  echo
  usage
}



# Checks the arguments validity
# $1 Path to the project root
# Exits if the arguments are invalid
function check_arguments()
{
  # Check for help / version parameter
  if [[ $1 == "-h" || $1 == "--help" ]]; then
    help
    exit 0
  fi

  if [[ $1 == "-v" || $1 == "--version" ]]; then
    version
    exit 0
  fi


  # The path must be provided
  if [[ $# -ne 1 ]]; then
    echo ""
    echo "Invalid Arguments $*"
    echo "One argument expected (path to the project root)"
    usage "$0"
    exit 1
  fi

  # The argument must be a directory
  if [[ ! -d "$1" ]]; then
    echo ""
    echo "Expected the root path of the project"
    usage "$0"
    exit 1
  fi

  # The path must contain some headers
  if [[ ! $(find "$1" -name \*.hh) ]]; then
    echo ""
    echo "Some header must exits in the given path"
    usage "$0"
    exit 1
  fi

  # A main must be at the root
  if [[ ! -f "${1}/main.cc" ]]; then
    echo ""
    echo "The main was not found in the given path"
    usage "$0"
    exit 1
  fi
}



function check_header()
{
  # Sanity check
  if [[ $# -ne 2 ]]; then
    echo "$COLOR_RED" # new line
    echo "IMPLEMENTATION ERROR: Invalid Arguments $*"
    echo "One argument expected (header name)"
    echo -n "$COLOR_NORMAL"
    exit 2
  fi

  local ret_val=0
  local header="$1"
  local source="$2"

  echo -n "Checking $header ..."

  # Compiling the header in stand-alone
  $COMPILE "$header"
  local ret_val=$(($? + ret_val))

  # Compiling a trivial main (with 2 inclusions to check the guards)
  header_in_src=${header##$source}
  test_header="${TMP_SRC}/test_header.cc"
  echo "#include \"$header_in_src\"" > $test_header
  echo "#include \"$header_in_src\"" >> $test_header
  echo "int main() { return 0; }" >> $test_header
  $COMPILE "$test_header"
  if [ $? -eq 0 ]; then
    echo -n "$COLOR_GREEN done"
  else
    echo -n "$COLOR_RED fail"
  fi
  echo "$COLOR_NORMAL"

  return $ret_val
}



function main()
{
  local ret_val=0 # Compilations return values accumulator

  check_arguments "$@"

  rm -rf "${TMP_SRC}"
  mkdir "${TMP_SRC}"
  cp -a "$1"/. "${TMP_SRC}"

  echo "Checking headers in $1"
  for header in $(find "$1" -name \*.hh); do
    check_header $header $1
    ret_val=$(($? + ret_val))
  done

  if [[ $ret_val -ne 0 ]]; then
    echo
    echo -e "\t $COLOR_RED NOT EVERY INCLUDE PASSED THE TEST $COLOR_NORMAL"
    exit 1
  fi

  echo
  echo -e "$COLOR_GREEN Every header complied $COLOR_NORMAL"
}


main "$@"
