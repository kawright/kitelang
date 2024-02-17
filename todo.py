#!/usr/bin/env python3

# Copyright (C) 2024  KA Wright

###############################################################################
# todo.py - Show all TODO lines in the project
###############################################################################

from os import system

TARGS = [
    "src",
    "example",
    "build.py",
    "CHANGELOG.md",
    "README.md"
]

def main():
    system("clear")
    cmd = 'grep -rn "TODO"'
    for targ in TARGS:
        cmd += f" {targ}"
    system(cmd)

if __name__ == "__main__":
    main()
