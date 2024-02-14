// Copyright (C) 2024  KA Wright

/******************************************************************************
err.h - API for reading and writing to the global error state.
******************************************************************************/

#ifndef __ERR_H__
#define __ERR_H__


/******************************************************************************
Stores all supported error codes.
******************************************************************************/
typedef enum {
    ErrCode_OK,
    ErrCode_RUNTIME,
    ErrCode_ARGV,
    ErrCode_MEM,
    ErrCode_BOUNDS
} ErrCode;


/******************************************************************************
Get the value of an `ErrCode` instance.
******************************************************************************/
int ErrCode_getVal(ErrCode this);


/******************************************************************************
Get the current error code. If no error has been signaled, `ErrCode_OK` will
be returned.
******************************************************************************/
ErrCode ErrState_getCode();


/******************************************************************************
Get the current error message. If no error has been signaled, an empty string
is returned.
******************************************************************************/
char *ErrState_getMsg();


/******************************************************************************
Set a new error code.
******************************************************************************/
void ErrState_setCode(ErrCode val);

/******************************************************************************
Set a new error message.

If `val` exceeds 127 characters in length, the message will not written and
this function will exit immediately.
******************************************************************************/
void ErrState_setMsg(char* val);


/******************************************************************************
Reset the global error state. The default code is `ErrCode_OK` and the default
message is an empty string.
******************************************************************************/
void ErrState_reset();


#endif
