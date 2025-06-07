#!/bin/bash
set -e

BUILD_DIR="build"
BUILD_TYPE="Release"

if [ ! -d "$BUILD_DIR" ]; then
  echo "Configuring project..."
  cmake -S . -B "$BUILD_DIR" -G Ninja -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
else
  echo "Build directory already exists."
fi

echo "Building project..."
cmake --build "$BUILD_DIR" --clean-first
