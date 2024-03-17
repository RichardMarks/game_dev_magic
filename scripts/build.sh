#!/usr/bin/env bash

# clean build directory
if [ -d "build" ]; then
  echo "Cleaning build directory"
  rm -rf build/
fi

mkdir -p build
mkdir -p dist

# generate build files
echo "Generating build files"
cmake -B build/

# Check if cmake command failed
if [ $? -ne 0 ]; then
  echo "CMake command failed. Exiting the script."
  exit 1
fi

echo "Building project"
# build project
cd build
make

# Check if make command failed
if [ $? -ne 0 ]; then
  echo "Make command failed. Exiting the script."
  cd ..
  exit 1
fi

cd ..

if [ -d "assets" ]; then
  echo "Copying assets to dist directory"
  cp -R assets/ dist/
fi

