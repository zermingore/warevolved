#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Expecting a replay file as argument"
  exit 2
fi


output="$1_generated_test"
echo -n > "$output"
i=10
screen_shot_found=0
while read line; do
  if [[ ${line:0:1} == '#' ]]; then
    echo "skipping: $line" >> "$output"
    continue
  fi

  echo "$line" | sed "s/.* /${i} /g" >> "$output"
  i=$((i + 10))

  # Check for screen-shot inputs
  if [[ $(echo ${line:-2:-1} | tail -c 3) == ' 3' ]]; then
    screen_shot_found=1
  fi
done < "$1"

if [[ $screen_shot_found == 0 ]]; then
  echo "WARNING: Did not find a screenshot input"
fi

echo "Generated test replay file in $output"
