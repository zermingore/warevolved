#!/bin/sh


# Crew management, testing:
# - Boarding a Vehicle
# - Picking up a Unit
# - Dropping a Crew member




# Move a Unit; confirm on its origin cell -> freeze

echo ${BASH_SOURCE%.*}
timeout 3 "${BIN_WE}" \
        -r --replay-file=${BASH_SOURCE%.*}.replay \
        --load-map=${BASH_SOURCE%.*}.map \
        >> /dev/null
if [[ $? -ne 0 ]]; then
  echo "Failure playing the replay -> abort"
  exit 1
fi


#diff -q "${}"





return 0
