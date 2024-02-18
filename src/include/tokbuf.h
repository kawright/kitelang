// Copyright (C) 2024  KA Wright

/******************************************************************************
tokbuf.h - API for token buffer
******************************************************************************/

#ifndef __TOKBUF_H__
#define __TOKBUF_H__


#include "tok.h"

/******************************************************************************
Opaque handle for a token buffer.
******************************************************************************/
typedef struct __TOK_BUF__ *TokBuf;


/******************************************************************************
Create an empty token buffer.

Sets `ErrCode_MEM` if heap-memory allocation fails.
******************************************************************************/
TokBuf TokBuf_new();


/******************************************************************************
Delete a `TokBuf`.
******************************************************************************/
void TokBuf_del(TokBuf this);


/******************************************************************************
Push a token onto a `TokBuf`.

Sets `ErrCode_MEM` if heap-memory allocation fails.
******************************************************************************/
void TokBuf_push(TokBuf this, Tok val);


/******************************************************************************
Advance the cursor of a `TokBuf` one position forward.

Sets `ErrCode_BOUNDS` if the operation will result in the cursor being
out-of-bounds.
******************************************************************************/
void TokBuf_adv(TokBuf this);


/******************************************************************************
Get the token in a `TokBuf` at the current cursor position.
******************************************************************************/
Tok TokBuf_get(TokBuf this);


/******************************************************************************
Get the token in a `TokBuf` one position ahead of the cursor.

Sets `ErrCode_BOUNDS` and returns `-1` if the cursor is already at the end of
the buffer.
******************************************************************************/
Tok TokBuf_peek(TokBuf this);


#endif
