# Cat Test

# Avoiding to quit the game -> blacklisting exit event
# TODO Prevent exit event only on the map
# TODO Do not hard-code the shuffle range
# TODO Do not hard-code the timeout / number of events

# Sanity checks
if [[ -z "$ROOT_TESTS" || -z "$BIN_WE" ]]; then
  echo
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS or BIN_WE not set"
  printError "[IMPLEMENTATION ERROR] $0 ROOT_TESTS: [$ROOT_TESTS] "
  exit 2
fi



TMP="${ROOT_TESTS}/we_replay_test_random__$(date +'%Y_%m_%d__%H_%M_%S')"


# Generate 1 input every millisecond
for (( i=1; i < 10000; i++ )); do # hard-coded
  random_input=$(shuf -i 0-10 -n 1)
  while [ $random_input = 6 ]; do
    if [[ "$random_input" = 6 ]]; then # remove exits
      random_input=$(shuf -i 0-10 -n 1)
    fi
  done
  echo "$((i * 2)) $random_input" >> "$TMP"
done

echo "Test file: $TMP"

timeout 10 "${BIN_WE}" -r --replay-file="$TMP" >> /dev/null

if [ $? -eq 124 ]; then
  return 0
fi
return 1
