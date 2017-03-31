# Fetch the enum class values and content
#
# Exits with the status
#   7 if the abort token was found while parsing the file


BEGIN {
  print "_______________ Fetching enums _______________"
  in_enum=0 # currently parsing an enum
}

END {
  print "____________ done fetching enums _____________"
}

BEGINFILE {
  print "Fetching enums in $FILENAME"
}

# Debug: Allow skipping the rest of the file
/ABORT/ {
  print "Found abort token, aborting"
  exit 7
}


# Skip lines which are only inline comments
/^\s*\/\// {
  next
}

# enum found
/enum\ class/ {
  in_enum=1
  current_enum=$3


  print "in:"
  print
  print ">>>>>>>>>> found enum " current_enum

  next
}


# Enum begin
/\s*{.*/ {
  next
}

# Enum end
/.*};.*/ {
  in_enum=0
  print "---------- end enum"
  print ""
  next
}

/.*/ {
  if (in_enum == 0)
    next

  print
}



# multilines
# (get lines between two patterns) -> flags
