// Copyright (C) 2024  KA Wright

/******************************************************************************
kite.c - Contains the entry point for the `kite` interpreter.
******************************************************************************/

#include <stdio.h>

#include "argvparse.h"
#include "err.h"

/******************************************************************************
main
******************************************************************************/
int main(int argc, char* argv[]) {
    ArgvParse parser = ArgvParse_new(argc, argv);
    if (ErrState_getCode() != ErrCode_OK) {
        fprintf(stderr, "%s\n", ErrState_getMsg());
        return ErrCode_getVal(ErrState_getCode());
    }   
 
    printf("Filename = %s\n", ArgvParse_getFile(parser));
    printf("Is Lex Only? = %d\n", ArgvParse_getIsLexOnly(parser));
    
    // CLEANUP:
    ArgvParse_del(parser);

    return 0;
}
