#!/bin/bash

# configure the projects, and build in a specific directory

BUILD_DIR=build # build destination

autoreconf --force --install --warnings=all

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
pushd "$BUILD_DIR"

../configure # TODO find the configure wherever the build folder is
make

popd # "$BUILD_DIR"
