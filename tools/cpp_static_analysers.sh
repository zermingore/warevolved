#!/bin/sh

find src/ -name \*.cc -exec \
     clang-tidy --checks=* {} \
     -- -Ilib/ -Isrc/ -std=c++2a -DDEBUG \;


cppcheck -Isrc/ --enable=all -i lib/ src/
