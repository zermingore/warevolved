# Display per unit the build time
#
# The following is required to let gcc compute the time per file
# WE_EXTRA_CXXFLAGS='-ftime-report' make -C build/ clean all V=1 > build_log 2>&1
#
# Warning: Only gcc compatible
#
# Arguments:
#   $1: build log with time information



BEGIN {
  file_name = "" # Current file beeing compiled
  total_time = 0
}



END {
  printf "\nTotal compilation time: %.3f\n", total_time
}



# Collecting wall total time
# Warning: g++ specific; not clang++ compliant
/TOTAL/ {
  if (file_name == "") {
    print "ERROR: Unable to determine which file is currently being compiled"
    exit 3
  }

  total_time = total_time + $5
  printf "%ss to compile [%s]\n", $5, file_name
  next
}



# File name (compiler call)
/g++.*\.cc/ {
  file_name = $NF
  next
}



# Irrelevant line
/.*/ {
  next
}
