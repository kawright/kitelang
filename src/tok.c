// Copyright (C) 2024  KA Wright

/******************************************************************************
tok.c - Implementation of token API.
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "tok.h"

/******************************************************************************
TokType_getName
******************************************************************************/
char *TokType_getName(TokType this) {
    switch (this) {
        case (TokType_STR):
            return "STR";
        case (TokType_NAME):
            return "NAME";
        case (TokType_OP):
            return "OP";
        case (TokType_PUNCT):
            return "PUNCT";
        case (TokType_END):
            return "END";
        case (TokType_SPEC):
            return "SPEC";
        default:
            return "";
    }
}

/******************************************************************************
__TOK__
******************************************************************************/
struct __TOK__ {
    TokType type;
    char *val;
};

/******************************************************************************
Tok_new
******************************************************************************/
Tok Tok_new(TokType type, char *val) {
    Tok ret = malloc(sizeof(struct __TOK__));
    if (ret == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Couldn't allocate `Tok`");
        return NULL;
    }
    ret->type = type;
    
    if (val == NULL) {
        ret->val = NULL;
        return ret;
    }

    ret->val = malloc(strlen(val));
    if (ret->val == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Couldn't allocate `Tok` value");
        free(ret);
        return NULL;
    }
    strcpy(ret->val, val);
    return ret;
}

/******************************************************************************
Tok_del
******************************************************************************/
void Tok_del(Tok this) {
    free(this->val);
    free(this);
}

/******************************************************************************
Tok_getType
******************************************************************************/
TokType Tok_getType(Tok this) {
    return this->type;
}

/******************************************************************************
Tok_getVal
******************************************************************************/
char *Tok_getVal(Tok this) {
    return this->val;
}
