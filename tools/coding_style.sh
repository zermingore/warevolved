#!/bin/bash

# Checks the coding stlye
# - The maximal lines length

# Global constants
MAX_COLUMNS=81



function usage()
{
    echo -e "\n\t./$(basename "$0") path_to_project_sources"
}

function version()
{
    echo -e "$(basename "$0") Version 1.0.0"
}

function help()
{
    echo
    echo "Check the coding style of the project"
    echo "Currently checks:"
    echo "- The maximal line length (${MAX_COLUMNS} columns, including '\\n')"
    echo
    echo "  -h --help    display this help"
    echo "  -v --version display the program version"
    echo
    echo "                              Written for War Evolved"
    echo
    usage
}


# Checks the arguments validity
# $1 Path to the project sources
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
        echo "One argument expected (path to the project sources)"
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
}



function check_lines_length()
{
    find "$1" -name \*.hh -o -name \*.cc | xargs grep -H ".\{${MAX_COLUMNS},\}"
}


function main()
{
    check_arguments "$@"

    check_lines_length "$1"
}


main "$@"
