// Copyright (C) 2024  KA Wright

/*
kite.c - Contains the entry point for the `kite` interpreter.
*/

#include <stdio.h>

#include "err.h"

/*
Entry point for the `kite` interpreter.
*/
int main(int argc, char* argv[]) {
    ErrState_setMsg("Hello, world!");
    puts(ErrState_getMsg());
    return ErrCode_getVal(ErrState_getCode());
}
