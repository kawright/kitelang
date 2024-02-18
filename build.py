#!/usr/bin/env python3

# Copyright (C) 2024  KW Wright

###############################################################################
# build.py - Build script for the `kitelang` project.
###############################################################################

from os import system

OBJS = [
    "argvparse",
    "err",
    "lex",
    "scanbuf",
    "tok",
    "tokbuf"
]

FLAGS = "-Isrc/include -g -Wall"

def main():
    print("Cleaning build artifacts")
    system("rm -Rf build")

    print("Creating build directory structure")
    system("mkdir build")
    system("mkdir build/obj")
    system("mkdir build/bin")

    print ("Building object files")
    for obj in OBJS:
        system(f"gcc {FLAGS} -c src/{obj}.c -o build/obj/{obj}.o")

    print("Building executable")
    cmd = f"gcc {FLAGS} -o build/bin/kite"
    for obj in OBJS:
        cmd += f" build/obj/{obj}.o"
    cmd += " src/kite.c"
    system(cmd)
    
    
    print("Done!")

if __name__ == "__main__":
    main()

