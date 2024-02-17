// Copyright (C) 2024  KA Wright

/******************************************************************************
kite.c - Contains the entry point for the `kite` interpreter.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "argvparse.h"
#include "err.h"
#include "initstage.h"
#include "lex.h"
#include "scanbuf.h"
#include "tok.h"

/******************************************************************************
MACRO: Panic for all error codes aside from OK. If in panic, free resources
according to the given initialization stage.
******************************************************************************/
#define FATAL_CHK()\
    if (ErrState_getCode() != ErrCode_OK) {\
        switch (initStage) {\
            case InitStage_SCANBUF_LOAD:\
                ScanBuf_del(buf);\
            case InitStage_ARGVPARSE_LOAD:\
                ArgvParse_del(parser);\
            case InitStage_BEGIN:\
            default:\
                break;\
        }\
        fprintf(stderr, "%s\n", ErrState_getMsg());\
        return ErrCode_getVal(ErrState_getCode());\
    }

/******************************************************************************
main
******************************************************************************/
int main(int argc, char* argv[]) {

    ArgvParse parser = NULL;
    ScanBuf buf = NULL;
    Tok currTok = NULL;    

    InitStage initStage = InitStage_BEGIN;

    parser = ArgvParse_new(argc, argv);
    FATAL_CHK()
    initStage = InitStage_ARGVPARSE_LOAD;

    FILE *fp = fopen(ArgvParse_getFile(parser), "rb");
    if (fp == NULL) {
        ErrState_setCode(ErrCode_FILEIO);
        ErrState_setMsg("Could not read source file");
        FATAL_CHK()
    }
    fseek(fp, 0, SEEK_END);
    long srcSz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *src = malloc(srcSz + 1);
    FATAL_CHK()
    fread(src, srcSz, 1, fp);
    src[srcSz] = '\0';    
    fclose(fp);
    buf = ScanBuf_new(src);
    FATAL_CHK()
    initStage = InitStage_SCANBUF_LOAD;

    currTok = Lex_next(buf);
    while (Tok_getType(currTok) != TokType_END) {
        FATAL_CHK()
        printf("<%s, %s>\n", TokType_getName(Tok_getType(currTok)), 
            Tok_getVal(currTok));
        Tok_del(currTok);
        currTok = Lex_next(buf);
    } 
    printf("<%s, %s>\n", TokType_getName(Tok_getType(currTok)), 
        Tok_getVal(currTok));
    
    // CLEANUP: 
    ScanBuf_del(buf);
    ArgvParse_del(parser);
    
    return 0;
}
