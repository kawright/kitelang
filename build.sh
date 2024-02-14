# Copyright (C) 2024  KW Wright

# build.sh - Build script for the `kitelang` project.

echo "Cleaning build artifacts"
rm -Rf build

echo "Creating build directory structure"
mkdir build
mkdir build/obj
mkdir build/bin

echo "Building object files"
gcc -Isrc/include -c src/err.c -o build/obj/err.o
gcc -Isrc/include -c src/scanbuf.c -o build/obj/scanbuf.o

echo "Building executable"
gcc -Isrc/include -o build/bin/kite     build/obj/err.o \
                                        build/obj/scanbuf.o \
                                        src/kite.c
