function _version()
{
  echo "$0 v${VERSION}"
}



function _help()
{
  echo "Usage:"
  echo -n "    $0 [--smoke] [--regression] [--no-configure]"
  echo    " [--parallel-build] [--tests=TEST_1,...,TEST_N] [--random-seed=VAL]"

  echo
  echo "Options:"
  local longest_opt=20 # longest option name + 1
  printf "    %-${longest_opt}s%s\n"\
         "-h|--help"    "print this help and exit"

  printf "    %-${longest_opt}s%s\n"\
         "-v|--version" "print the program version ($VERSION) and exit"

  printf "    %-${longest_opt}s%s\n"\
         "--safe-mode" "out of tree build, based on tracked files; run tests"

  printf "    %-${longest_opt}s%s\n"\
         "-j|--parallel-build" "Run make in parallel (--jobs)"

  printf "    %-${longest_opt}s%s\n"\
         "-n|--no-configure" "Do not run autoreconf / configure (no clean)"

  printf "    %-${longest_opt}s%s\n"\
         "--random-seed=VALUE"\
         "Use the given seed to initialize the random generator"

  printf "    %-${longest_opt}s%s\n"\
         "-r|--regression"\
         "Run the regression tests (exclude other non specified types)"

  printf "    %-${longest_opt}s%s\n"\
         "-i|--integration"\
         "Run the integration tests (exclude other non specified types)"

  printf "    %-${longest_opt}s%s\n"\
         "-s|--smoke" "Run the smoke tests (exclude other non specified types)"

  printf "    %-${longest_opt}s%s\n"\
         "--tests=TEST1,TEST2" "Run the specified tests cases only"

  echo
  echo "Examples:"
  echo "    Clean build, run all tests"
  echo "    $0"
  echo
  echo "    Partial parallel build, run only the regression tests"
  echo "    $0 --no-configure -j --regression"
  echo
  echo "    Run a specific test without configure"
  echo "    $0 -n -j --tests=tests/regression/escape_map.sh,tests/path/basic.sh"
  echo
  echo "    What a git push hook should do (out of tree build, run every test)"
  echo "    $0 --safe-mode"
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
  local getopt_ret
  getopt --test || getopt_ret=$?
  if [ $getopt_ret -ne 4 ]; then
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

      -v|--version)
        _version
        exit 0
        ;;

      --safe-mode)
        SAFE_MODE=1
        shift
        ;;

      -j|--parallel-build)
        PARALLEL_BUILD="-j$(grep -c processor /proc/cpuinfo)"
        shift
        ;;

      -n|--no-configure)
        NO_CONFIGURE=1
        shift
        ;;

      --random-seed)
        RANDOM_SEED=$2
        shift 2
        ;;

      -i|--integration)
        RUN_ALL_TYPES=0
        RUN_INTEGRATION=1
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
