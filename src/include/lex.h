// Copyright (C) 2024  KA Wright

/******************************************************************************
lex.h - API for lexers.
******************************************************************************/

#ifndef __LEX_H__
#define __LEX_H__

#include "scanbuf.h"
#include "tok.h"


/******************************************************************************
Get the next token from a `ScanBuf`. If all other tokens have already been
returned, a token of `TokType_END` will be returned with a `NULL` value. `NULL`
is returned for all error conditions.

Sets `ErrCode_MEM` if heap-memory allocation fails.

Sets `ErrCode_ILLEGAL` if an illegal character is encountered.

Sets `ErrCode_BOUNDS` if the end of the buffer is reached mid-string.
******************************************************************************/
Tok Lex_next(ScanBuf buf);


#endif
