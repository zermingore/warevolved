# Segfault canceling on the menu map

TMP=/tmp/we_replay_test
echo '1 6' > "$TMP" # escape after 1ms

timeout 2 "${BIN_WE}" -r --replay-file="$TMP" >> /dev/null
if [[ $? -eq 124 ]]; then
  return 0
fi

return 1
