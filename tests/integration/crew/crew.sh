#!/bin/sh


# Crew management, testing:
# - Boarding a Vehicle
# - Picking up a Unit (with / without move)
# - Dropping a Crew member (with / without move)
# - Moving an empty vehicle


timeout 90 "${BIN_WE}" \
        -r --replay-file=${BASH_SOURCE%.*}.replay \
        --load-map=${BASH_SOURCE%.*}.map.ori \
        >> /dev/null
if [[ $? -ne 0 ]]; then
  echo "Failure playing the replay -> abort"
  exit 1
fi


# Retrieve saved map file name
SAVED_MAP=$(grep "Saving map into:" "$(pwd)/LOG" \
              | awk '{ print $NF }')
SAVED_MAP=${SAVED_MAP%xml*}xml # Trim color characters

diff "${BASH_SOURCE%.*}.map.ref" "$(dirname $(readlink -f $0))/../${SAVED_MAP}"

return $?
