// Copyright (C) 2024  KA Wright

/******************************************************************************
argvparse.c - Argument parsing implementation
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "argvparse.h"
#include "err.h"


/******************************************************************************
__ARGV_PARSE__
******************************************************************************/
struct __ARGV_PARSE__ {
    char *file;
    int isLexOnly;
};

/******************************************************************************
ArgvParse_new
******************************************************************************/
ArgvParse ArgvParse_new(int argc, char *argv[]) {
    ArgvParse ret = malloc(sizeof(struct __ARGV_PARSE__));
    if (ret == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Couldn't allocate argument parser");
        return NULL;
    }
    ret->file = NULL;
    ret->isLexOnly = 0;

    for (int i=1; i<argc; i++) {
        
        // Handle options:
        if (argv[i][0] == '-') {
            if (strlen(argv[i]) == 1) {
                ErrState_setCode(ErrCode_ARGV);
                ErrState_setMsg("Empty tack");
                free(ret);
                return NULL;
            }
            
            // Long options:
            if (argv[i][1] == '-') {
                if (strcmp(argv[i], "--lex-only") == 0) {
                    if (ret->isLexOnly == 1) {
                        ErrState_setCode(ErrCode_ARGV);
                        ErrState_setMsg("--lex-only already given");
                        free(ret);
                        return NULL;
                    }
                    ret->isLexOnly = 1;
                    continue; 
                } else {
                    ErrState_setCode(ErrCode_ARGV);
                    ErrState_setMsg("Illegal long option given");
                    free(ret);
                    return NULL;
                }
            
            // Short options:
            } else {
                for (int j=1; j<strlen(argv[i]); j++) {
                    switch (argv[i][j]) {
                        case 'l':
                            if (ret->isLexOnly == 1) {
                                ErrState_setCode(ErrCode_ARGV);
                                ErrState_setMsg("--lex-only already given");
                                free(ret);
                                return NULL;
                            }
                            ret->isLexOnly = 1;
                            break;
                        default:
                            ErrState_setCode(ErrCode_ARGV);
                            ErrState_setMsg("Illegal short option given");
                            free(ret);
                            return NULL;
                    }
                }
                continue;
            }
            
        } else {
            if (ret->file != NULL) {
                ErrState_setCode(ErrCode_ARGV);
                ErrState_setMsg("Filename already given");
                free(ret);
                return NULL;
            }
            ret->file = strdup(argv[i]);
            if (ret->file == NULL) {
                ErrState_setCode(ErrCode_MEM);
                ErrState_setMsg("Couldn't allocate argv parser");
                free(ret);
                return NULL;
            }
        }
    }
    if (ret->file == NULL) {
        ErrState_setCode(ErrCode_ARGV);
        ErrState_setMsg("Filename not given");
        free(ret);
        return NULL;
    }
    return ret;
}

/******************************************************************************
ArgvParse_del
******************************************************************************/
void ArgvParse_del(ArgvParse this) {
    free(this->file);
    free(this);
}

/******************************************************************************
ArgvParse_getFile
******************************************************************************/
char *ArgvParse_getFile(ArgvParse this) {
    return this->file;
}

/******************************************************************************
ArgvParse_getIsLexOnly
******************************************************************************/
int ArgvParse_getIsLexOnly(ArgvParse this) {
    return this->isLexOnly;
}
