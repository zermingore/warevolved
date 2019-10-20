#!/bin/sh

# Small script to output the first creation date of a file
# (supports renames and suppression)


for file in "$@"; do
    echo "$file"
    git log --diff-filter=A --follow --format=%aD -- "$file" | tail -n 1
done
