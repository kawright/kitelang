// Copyright (C) 2024  KA Wright

/******************************************************************************
err.c - Implementation of the global error state API.
******************************************************************************/

#include <string.h>

#include "err.h"

#define MAX_MSG_LEN 127

ErrCode __code__;
char __msg__[MAX_MSG_LEN + 1];

/******************************************************************************
ErrCode_getVal
******************************************************************************/
int ErrCode_getVal(ErrCode this) {
    switch (this) {
        case ErrCode_OK:
            return 0;
        case ErrCode_RUNTIME:
            return 1;
        case ErrCode_ARGV:
            return 2;
        case ErrCode_MEM:
            return 3;
        case ErrCode_BOUNDS:
            return 4;
        case ErrCode_ILLEGAL:
            return 5;
        default:
            return 1;
    }
}


/******************************************************************************
ErrState_getCode
******************************************************************************/
ErrCode ErrState_getCode() {
    return __code__; 
}

/******************************************************************************
ErrState_getMsg
******************************************************************************/
char *ErrState_getMsg() {
    return __msg__;
}

/******************************************************************************
ErrState_setCode
******************************************************************************/
void ErrState_setCode(ErrCode val) {
    __code__ = val;
}

/******************************************************************************
ErrState_setMsg
******************************************************************************/
void ErrState_setMsg(char* val) {
    if (strlen(val) <= MAX_MSG_LEN) {
        strcpy(__msg__, val);
    }
}

/******************************************************************************
ErrState_reset
******************************************************************************/
void ErrState_reset() {
    __code__ = ErrCode_OK;
    strcpy(__msg__, "");
}
