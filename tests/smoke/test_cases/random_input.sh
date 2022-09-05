# Cat Test

# Avoiding to quit the game -> blacklisting exit event
# TODO Prevent exit event only on the map
# TODO Do not hard-code the shuffle range
# TODO Do not hard-code the timeout / number of events

set +x # do not spam too much (random generation)


# Sanity checks
if [[ -z "$ROOT_TESTS" || -z "$BIN_WE" ]]; then
  echo
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS or BIN_WE not set"
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS: [$ROOT_TESTS] "
  exit 2
fi


RANDOM=$RANDOM_SEED
TMP="${ROOT_TESTS}/we_replay_test_random__$(date +'%Y_%m_%d__%H_%M_%S')"
echo "# seed: $RANDOM_SEED" >> $TMP


# Returns a random value belonging to the given range (inclusively)
# Warning: *MUST* run in a sub-shell
# $1 Random seed
# $2 Range lower bound
# $3 Range upper bound
function get_random_value()
{
  if [[ $# -ne 3 ]]; then
    echo "Invalid arguments $#"
    exit 234
  fi

  # Initialize the seed in the sub-shell
  RANDOM=$1
  echo $(((RANDOM + $2) % $3))
}



# Generate 1 input every millisecond
for (( i=1; i < 10000; i++ )); do # hard-coded
  tmp=$RANDOM
  random_input=$(get_random_value $tmp 0 10)
  while [ $random_input = 6 ]; do # remove 'exit' events
    tmp=$RANDOM
    random_input=$(get_random_value $tmp 0 10)
  done
  echo "$((i * 2)) $random_input" >> "$TMP"
done

echo "Test file: $TMP"


set -x # re-activate output

timeout 10 "${BIN_WE}" \
        --random-seed="$RANDOM_SEED" -r --replay-file="$TMP" > "/tmp/we_log_test"
if [ $? -eq 124 ]; then
  return 0
fi

chmod -w "$TMP"
return 1
