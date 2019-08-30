#!/bin/bash

# Checks the coding stlye
# - The maximal lines length

# Global constants
MAX_COLUMNS=81

# Colors for fancy prints
COLOR_RED=$(echo -e '\e[0;31m')
COLOR_GREEN=$(echo -e '\e[0;32m')
COLOR_YELLOW=$(echo -e '\e[0;33m')
COLOR_NORMAL=$(echo -e '\e[0m')



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
    local lines=$(find "$1" -name \*.hh -o -name \*.cc | xargs grep -H ".\{${MAX_COLUMNS},\}")
    if [[ $lines != "" ]]; then
        echo "${COLOR_RED}Too long lines detected:${COLOR_NORMAL}"

        # Printing the too long lines
        IFS=$'\n'
        for l in $lines; do
            echo "${COLOR_YELLOW}>${MAX_COLUMNS} col:${COLOR_NORMAL} $l"
        done
        unset IFS
    else
        echo "${COLOR_GREEN}Maximal line length respected ($MAX_COLUMNS columns with \\n)${COLOR_NORMAL}"
    fi
}



function check_tabs()
{
    local lines=$(grep -rn -P '\t' "$1" --exclude=*.in)
    if [[ $lines != "" ]]; then
        echo "${COLOR_RED}Tabs detected:${COLOR_NORMAL}"

        # Printing faulty lines
        IFS=$'\n'
        for l in $lines; do
            echo "$l"
        done
        unset IFS
    else
        echo "${COLOR_GREEN}No tab detected${COLOR_NORMAL}"
    fi
}



function main()
{
    check_arguments "$@"

    check_lines_length "$1"
    check_tabs "$1"
}


main "$@"
