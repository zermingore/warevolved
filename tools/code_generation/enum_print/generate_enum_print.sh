#!/bin/bash

# Generates a mapping enum value -> enum value name as a string
#
# WARNING: enums are fetch in header files (.hh) only
# WARNING: enums must be in global namespace
# NOTE: The given enum file must be compilable
#
# gen getter / print / operator ?
# return an array: {enum_name, val1, val2, ... } ?



if [[ $# -ne 1 ]]; then
  echo "$0: expected one argument: project root folder"
  exit 1
fi

WE_PATH=$(readlink -f "$1")
OUTPUT_DIR=/tmp/generated


# Builds a list of enum files (headers in enums/ folder)
function locate_enums_files()
{
  find "${WE_PATH}/src" -name \*.hh -type f
}


# Print the guard associated with the given filename
# Note: assumes the sub-folder 'generated'
#
# $1 Header filename
#
function print_header_guard()
{
  # Expecting the header file name
  if [[ $# -ne 1 ]]; then
    echo "${FUNCNAME[0]}: Expecting 1 filename, received: $@"
    exit 1
  fi
  local filename="$1"


  # generate the guard
  local trimmed_filename=$(basename "$filename" .hh)
  local guard=GENERATED_${trimmed_filename^^}_HH_

  echo "$guard"
}



# For the prototypes header, prints
# - The Doxygen comment
# - The header guards (only ifdef / ifndef)
# - The debug namespace begin
#
# $1 Prototype filename
#
function print_prototypes_head()
{
  # Expecting the prototypes file name
  if [[ $# -ne 1 ]]; then
    echo "${FUNCNAME[0]}: Expecting 1 filename, received: $@"
    exit 1
  fi
  local filename="$1"

  local clean_name
  clean_name=$(readlink -f $0)
  clean_name=${clean_name//"${WE_PATH}/"/}

  # Print the doxygen comment
  echo "/**"
  echo " * \author $(basename $0)"
  echo " * \brief Prototypes used to print the enums values"
  echo " * \note generated by $clean_name"
  echo " */"
  echo ""
  echo ""


  # Put the header guards (ifdef / ifndef)
  local guard=$(print_header_guard "$filename")
  echo "#ifndef $guard"
  echo "# define $guard"
  echo ""
}



function get_forward_declarations()
{
  local enums=$(locate_enums_files)
  for f in $enums; do
    grep 'enum class' $f | grep -v 'enum class.*;' | while read -r line ; do
    echo "${line};"
    done
  done
}



# Copy the prototypes from the files generated by awk into a single header
function handle_prototypes()
{
  local prototypes="$OUTPUT_DIR"/enum_print.hh

  # Put the doxygen header comment
  print_prototypes_head "$prototypes" > "$prototypes"

  # Copy the includes from the generated code (enum declarations)
  local gen_file
  gen_file=$(find "$OUTPUT_DIR" -name *.cc)

  echo -e '# include <string>\n' >> "$prototypes"
  # grep -rh '# *include' "$gen_file" | grep -v string >> "$prototypes"

  get_forward_declarations >> "$prototypes"

  # Debug namespace
  echo -e "\n\nnamespace debug {\n" >> "$prototypes"

  # Copy the prototypes from the generated code
  grep -rh std::string "$gen_file" | sed -e s/'\(.*\)'/'\1;'/g >> "$prototypes"

  # Close the namespace
  echo -e "\n} // namespace debug\n" >> "$prototypes"

  # Close the guard
  local guard=$(print_header_guard "$prototypes")
  echo -e "\n#endif /* !$guard */" >> "$prototypes"
}



# Generate the printEnum(e_enum value); function
# $1 list of enum files
function generate_print()
{
  if [[ $# -ne 1 ]]; then
    echo "${FUNCNAME[0]}: Expecting files list, received: $@"
    exit 1
  fi
  local enums_list="$1"

  local awk_gen="${OUTPUT_DIR}"/enum_print.cc


  # Adding header (comment, includes, namespace)
    cat << EOF_HEADING >> "$awk_gen"
/**
 * \file
 * \author $(basename $0)
 * \brief Wrapper enum <=> string
 * \warning auto-generated code, edit at your own risks
 */


#include <string>

#include <generated/enum_print/enum_print.hh>
EOF_HEADING


  # Handle enum includes
  for f in $enums_list; do
    # Ignore irrelevant files
    if [[ ! $(grep 'enum class' $f | grep -v 'enum class.*;') ]]; then
      continue
    fi

    local clean_name
    clean_name=$(readlink -f $f)
    clean_name=${clean_name//"${WE_PATH}/src/"/}

    echo "#include <${clean_name}>" >> "$awk_gen"
  done
  echo -e "\n\nnamespace debug {\n" >> "$awk_gen"


  # Getting useful files list
  for f in $enums_list; do
    # Ignore irrelevant files
    if [[ ! $(grep 'enum class' $f | grep -v 'enum class.*;') ]]; then
      continue
    fi

    local clean_name
    clean_name=$(readlink -f $f)
    clean_name=${clean_name//"${WE_PATH}/src/"/}

    # Trim comments
    # g++ -x c++ -E "$f" >> /tmp/$(basename "$f")
    cpp -dD -fpreprocessed -o /tmp/$(basename "$f") "$f"

    # Invoke the awk script, generating the code
    gawk -f $(dirname "$0")/fetch_enums.awk /tmp/$(basename "$f") >> "$awk_gen" # --lint
  done

  echo -e "\n} // namespace debug" >> "$awk_gen"
}


# Integrate the generated code into the project folder
function integrate_generation()
{
  local generated_folder="$WE_PATH"/src/generated/enum_print
  rm -rf "$generated_folder"
  mkdir -p "$generated_folder"
  cp -a "$OUTPUT_DIR"/* "$generated_folder"

  print_generated_list "$generated_folder"
}


# Print the list of files to build (to add in src/Makefile.am)
#
# $1 folder where generated files are
#
function print_generated_list()
{
  # Expecting folder containing the generated files
  if [[ $# -ne 1 ]]; then
    echo "${FUNCNAME[0]}: Expecting 1 folder name, received: $@"
    exit 1
  fi
  local generated_folder="$1"

  echo -e "\nYou can build the following file (check src/Makefile.am)"

  local source_list=$(find "$generated_folder" -name \*.c\*)
  for f in $source_list; do
    echo "generated/enum_print/"$(basename "$f")
  done
}


# ___________________________________ main ___________________________________ #
function main()
{
  rm -rf "$OUTPUT_DIR"
  mkdir -p "$OUTPUT_DIR"

  local enums=$(locate_enums_files)
  generate_print "$enums"
  handle_prototypes

  integrate_generation
}

main
