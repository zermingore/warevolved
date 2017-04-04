# Fetch the enum class values and content from the C++ provided file
# The file must not contain any comments. Use g++ -E or equivalent to remove them
# before calling this script (or else the behaviour is undefined)
#
# Arguments:
#   $1: source file name containing the enums
#
# Exits with the status
#   7 if the abort token was found while parsing the file


BEGIN {
  print "_______________ Fetching enums _______________\n\n"
  in_enum = 0    # Currently parsing an enum
  enum_name = "" # Current enum name
}

END {
  print "____________ done fetching enums _____________\n"
}

# BEGINFILE {
#   print "Fetching enums in $FILENAME"
# }

# Debug: Allow skipping the rest of the file
/ABORT/ {
  print "Found abort token, aborting"
  exit 7
}


# enum found
/enum\ class/ {
  in_enum = 1

  # Change the field separator (enum class NAME: int)
  old_fs = FS
  FS = "[ :]"

  # gsub(".*enum class(.*)","")
  gsub("enum class *","")
  enum_name = $1

  printf ">> Found enum |%s|\n", enum_name

  # Restore the current field separator
  FS = old_fs

  next
}


# Try to locate the enum begin
#/\s*{.*/ {


# Enum end
/.*};.*/ {
  printf "<< End enum |%s|\n\n", enum_name

  in_enum = 0
  enum_name = ""

  next
}


# enum values
/.*/ {
  if (in_enum != 1)
    next

  if ($0 == "{")
  {
    print "---------- Values ----------"
    next
  }


  # expecting entry [= val][,]
  old_fs = FS
  FS = "[=,]"

  # get the enum entry
  gsub("*","")
  value = $3
  printf "|%s|_", $1

  # get the value, excluding the eventual ','
  tab["empty"] = 1
  if (match(value, "(.*),", tab) == 0)
    printf "|%s|\n", $3
  else
    printf "|%s|\n", tab[1]


  FS = old_fs

  next
}
