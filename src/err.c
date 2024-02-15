// Copyright (C) 2024  KA Wright

/******************************************************************************
err.c - Implementation of the global error state API.
******************************************************************************/

#include <string.h>

#include "err.h"

#define MAX_MSG_LEN 127

ErrCode code;
char msg[MAX_MSG_LEN + 1];

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
    return code; 
}

/******************************************************************************
ErrState_getMsg
******************************************************************************/
char *ErrState_getMsg() {
    return msg;
}

/******************************************************************************
ErrState_setCode
******************************************************************************/
void ErrState_setCode(ErrCode val) {
    code = val;
}

/******************************************************************************
ErrState_setMsg
******************************************************************************/
void ErrState_setMsg(char* val) {
    if (strlen(val) <= MAX_MSG_LEN) {
        strcpy(msg, val);
    }
}

/******************************************************************************
ErrState_reset
******************************************************************************/
void ErrState_reset() {
    code = ErrCode_OK;
    strcpy(msg, "");
}
