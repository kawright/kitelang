# Copyright (C) 2024  KW Wright

# build.sh - Build script for the `kitelang` project.

echo "Cleaning build artifacts"
rm -Rf build

echo "Creating build directory structure"
mkdir build
mkdir build/obj
mkdir build/bin

echo "Building executable"
gcc -o build/bin/kite src/kite.c
