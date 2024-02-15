# Copyright (C) 2024  KW Wright

###############################################################################
# build.sh - Build script for the `kitelang` project.
###############################################################################

echo "Cleaning build artifacts"
rm -Rf build

echo "Creating build directory structure"
mkdir build
mkdir build/obj
mkdir build/bin

echo "Building object files"
gcc -Isrc/include -c src/err.c -o build/obj/err.o
gcc -Isrc/include -c src/lex.c -o build/obj/lex.o
gcc -Isrc/include -c src/scanbuf.c -o build/obj/scanbuf.o
gcc -Isrc/include -c src/tok.c -o build/obj/tok.o

echo "Building executable"
gcc -Isrc/include -o build/bin/kite     build/obj/err.o \
                                        build/obj/lex.o \
                                        build/obj/scanbuf.o \
                                        build/obj/tok.o \
                                        src/kite.c
