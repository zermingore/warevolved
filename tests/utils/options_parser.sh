function _version()
{
  echo "$0 v${VERSION}"
}



function _help()
{
  echo "Usage:"
  echo -n "    $0 [--smoke] [--regression] [--no-configure]"
  echo    " [--parallel-build] [--tests=TEST_1,...,TEST_N]"

  echo
  echo "Options:"
  local longest_opt=20 # longest option name + 1
  printf "    %-${longest_opt}s%s\n"\
         "-h|--help"    "print this help and exit"

  printf "    %-${longest_opt}s%s\n"\
         "-j|--parallel-build" "Run make in parallel (--jobs)"

  printf "    %-${longest_opt}s%s\n"\
         "-n|--no-configure" "Do not run autoreconf / configure (no clean)"

  printf "    %-${longest_opt}s%s\n"\
         "-r|--regression"\
         "Run the regression tests (exclude other non specified types)"

  printf "    %-${longest_opt}s%s\n"\
         "-s|--smoke" "Run the smoke tests (exclude other non specified types)"

  printf "    %-${longest_opt}s%s\n"\
         "--tests=TEST1,TEST2" "Run the specified tests cases only"

  printf "    %-${longest_opt}s%s\n"\
         "-v|--version" "print the program version ($VERSION) and exit"

  echo
  echo "Examples:"
  echo "    Clean build, run all tests (should be used before pushing changes)"
  echo "    $0"
  echo
  echo "    Partial parallel build, run only the regression tests"
  echo "    $0 --no-configure -j --regression"
  echo
  echo "$0 -n -j --tests=tests/regression/escape_map.sh,tests/path/basic.sh"
}



function _check_test_files_exist()
{
  local ret_val=0
  for test_file in "${TESTS_LIST[@]}"
  do
    if ! [ -f $test_file ]; then
      printError "Test file $test_file not found"
      ret_val=1
    fi
  done

  if [ $ret_val -ne 0 ]; then
    exit $ret_val
  fi
}



function parse_options()
{
  # Check getopt version compatible (GNU)
  getopt --test
  if [ $? -ne 4 ]; then
    printError "Non-supported getopt version"
    exit 1
  fi

  # Invoke getopt
  local ret_val_getopt
  local opts
  opts=$(getopt --options $OPTIONS \
                --long $OPTIONS_LONG \
                -- "$@")
  ret_val_getopt=$?
  if [ $ret_val_getopt -ne 0 ]; then
    printError "getopt returned ${ret_val_getopt}. Terminating..."
    exit $ret_val_getopt
  fi

  eval set -- "$opts"

  while true; do
    case "$1" in
      -h|--help)
        _help
        echo
        _version
        exit 0
        ;;

      -j|--parallel-build)
        PARALLEL_BUILD="-j$(grep -c processor /proc/cpuinfo)"
        shift
        ;;

      -n|--no-configure)
        NO_CONFIGURE=1
        shift
        ;;

      -r|--regression)
        RUN_ALL_TYPES=0
        RUN_REGRESSION=1
        shift
        ;;

      -s|--smoke)
        RUN_ALL_TYPES=0
        RUN_SMOKE=1
        shift
        ;;

      --tests)
        RUN_ALL_TYPES=0
        TESTS_LIST=(${2//,/ }) # Build an array of tests from the argument
        shift 2
        _check_test_files_exist
        ;;

      -v|--version)
        _version
        exit 0
        ;;

      --)
        shift
        break
        ;;

      *)
        _help
        printError "Invalid option $1"
        exit 1
        ;;
    esac
  done
  shift $((OPTIND-1))
}
