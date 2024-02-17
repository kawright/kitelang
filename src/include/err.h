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
    ErrCode_OK,             // No error
    ErrCode_RUNTIME,        // General error
    ErrCode_ARGV,           // Bad argv given
    ErrCode_MEM,            // Heap-memory allocation fail
    ErrCode_BOUNDS,         // Buffer out of bounds
    ErrCode_ILLEGAL,        // Illegal character found
    ErrCode_FILEIO          // File IO op fail
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
