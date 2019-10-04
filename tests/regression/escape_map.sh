# Segfault canceling on the menu map

TMP=/tmp/we_replay_test
echo '1 6' > "$TMP" # escape after 1ms

timeout 3 "${BIN_WE}" -r --replay-file="$TMP" >> /dev/null
return $?
