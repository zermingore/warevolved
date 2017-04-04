#!/bin/bash

# Generates a mapping enum value -> enum value name as a string
#
# NOTE: does not handle block comments over multiple lines
#       (if they contain the string 'enum class')
#
# /*
# enum class test*/
# will consider the enum test*/
# though /* enum class test */ will be ignored, as expected
#


WE_PATH=..



# Builds a list of enum files (headers in enums/ folder)
function locate_enums_files
{
    find $(find "${WE_PATH}" -name enums -type d) -name *.h*
}


# Extracts the enums class name in the given file
# $1: filename
function extract_enums
{
    if [[ $# -ne 1 ]]; then
        echo "${FUNCNAME[0]}: Expecting 1 filename, received: $@"
        exit 1
    fi

    file="$1"

    # extract relevant lines, remove 'enum class', block then inline comments
    enums=$(grep enum\ class\  "$file" \
                   | sed s~\ *enum\ class\ ~~ \
                   | sed s~'/\*.*\*/'~~g \
                   | sed s~//.*~~g)

    for e in $(echo "$enums"); do
        echo "$e"
    done
}


# Parse the given files, finding the enums
# $1 list of enums files to parse
function parse_files
{
    if [[ $# -ne 1 ]]; then
        echo "${FUNCNAME[0]}: Expecting 1 filename, received: $@"
        exit 1
    fi

    enums_files_list="$1"

    for file in "$enums_files_list"; do
        echo "Found: $file"
        grep -d skip enum\ class "$file"
    done
}


# Generate the printEnum(e_enum value); function
# $1 list of enum names
function generate_print()
{
    if [[ $# -ne 1 ]]; then
        echo "${FUNCNAME[0]}: Expecting 1 filename, received: $@"
        exit 1
    fi

    enums_list="$1"

    for enum in $(echo "$enums_list"); do
        echo ">> generating code for $enum"

        # prototype
        echo "void print${enum^}(e_$enum $enum);"

        # function
        echo "void print${enum^}(e_$enum $enum)"
        echo "{"
        echo "  switch($enum)"
        echo "  {"
        generate_switch_cases "$enum"
        echo "  {"
        echo "}"
    done
}


# Generates the body of the switch for a given enum
# $1 enum name
function generate_switch_cases()
{
    echo "___"
}



# ___________________________________ main ___________________________________ #
# enums_file_list=$(locate_enums_files)
# parse_files "$enums_file_list"


enums=$(extract_enums tools/enum_print_test)

generate_print "$enums"


# gen getter / print / operator ?

# return an array: {enum_name, val1, val2, ... } ?

# bash: multiple return values: prototype and function

# handle comments with gcc -E
# use awk -> enum names and values
# see also xmacros
