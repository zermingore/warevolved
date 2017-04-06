#!/bin/bash


# Generates a mapping enum value -> enum value name as a string
#
# NOTE: The given enum file must be compilable
#       and preprocessed, using gcc -E for instance
#


WE_PATH=..



# Builds a list of enum files (headers in enums/ folder)
function locate_enums_files
{
    find $(find "${WE_PATH}" -name enums -type d) -name *.h*
}



# Generate the printEnum(e_enum value); function
# $1 list of enum files
function generate_print()
{
    if [[ $# -ne 1 ]]; then
        echo "${FUNCNAME[0]}: Expecting 1 filename, received: $@"
        exit 1
    fi

    enums_list="$1"


    for f in $enums_file_list; do
        echo "Processing enums in $f"

        # Trim comments
        g++ -x c++ -E $f > /tmp/$(basename $f)

        # Invoke the awk script, generating the code
        awk -f $(dirname $0)/fetch_enums.awk /tmp/$(basename $f) \
            > /tmp/genrated_$(basename $f) # --lint
    done

}



# ___________________________________ main ___________________________________ #
enums_file_list=$(locate_enums_files)

generate_print "$enums"


# gen getter / print / operator ?
# return an array: {enum_name, val1, val2, ... } ?
