#!/bin/bash

# Check if the headers can be compiled separately.
# Compiles the headers


# Compiler and Flags
CXX=g++
CXXFLAGS="-O0 -pipe -DDEBUG -DDEBUG_LEAKS \
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
FAILED_LIST=${TMP_SRC}/__results__
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



# Check if the given header can be compiled
# Try to include it twice to check its idem-potency
#
# Arguments
#   header file
#   headers root
#
# Return nothing but write the file name in $FAILED_LIST on error
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

  local -r header="$1"
  local -r source="$2"

  # Compiling the header in stand-alone
  $COMPILE "$header"

  # Compiling a trivial main (with 2 inclusions to check the guards)
  header_in_src=${header##$source}
  local -r test_header="${TMP_SRC}/test_header__$(basename $header).cc"

  cat << EOF > $test_header
#include "$header_in_src"
#include "$header_in_src"
int main() { return 0; }
EOF
  $COMPILE "$test_header"
  if [ $? -eq 0 ]; then
    echo "${COLOR_GREEN}[PASS] ${COLOR_NORMAL}$header"
  else
    echo "${COLOR_RED}[FAIL] ${COLOR_NORMAL}$header"
    echo "$header" >> $FAILED_LIST
  fi
}



function main()
{
  check_arguments "$@"

  rm -rf "${TMP_SRC}"
  mkdir "${TMP_SRC}"
  echo "Any erroneous header will be listed here:" >> $FAILED_LIST
  cp -a "$1"/. "${TMP_SRC}"

  local -r nb_core=$((2 * $(nproc)))
  echo "Checking headers in $1"

  # Run the checks themselves
  for header in $(find "$1" -name \*.hh); do
    while [ $(jobs | wc -l) -ge $nb_core ]; do
      sleep 0.1
    done

    check_header $header $1 &
  done

  # Wait for non-terminated jobs
  while [ $(jobs | wc -l) -ne 1 ]; do
    sleep 0.1
  done

  if [[ $(cat $FAILED_LIST | wc -l) != "1" ]]; then
    echo
    echo -e "\t $COLOR_RED THE FOLLOWING INCLUDES FAILED THE TEST $COLOR_NORMAL"
    tail -n 1 $FAILED_LIST
    exit 1
  fi

  echo
  echo -e "$COLOR_GREEN Every header complied $COLOR_NORMAL"
}


main "$@"
