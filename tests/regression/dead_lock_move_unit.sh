# Move a Unit; confirm on its origin cell -> freeze

echo ${BASH_SOURCE%.*}
timeout 3 "${BIN_WE}" \
        -r --replay-file=${BASH_SOURCE%.*}.replay \
        --load-map=${BASH_SOURCE%.*}.map \
        > "/tmp/log_test_$0"
return $?
