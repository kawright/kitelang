// Copyright (C) 2024  KA Wright

/******************************************************************************
scanbuf.h - API for a scannable buffer which supports look-ahead.
******************************************************************************/

#ifndef __SCANBUF_H__
#define __SCANBUF_H__


/******************************************************************************
Opaque handle for a character buffer which can be scanned with one-character
look-ahead.
******************************************************************************/
typedef struct __SCAN_BUF__ *ScanBuf;


/******************************************************************************
Create a new `ScanBuf` from an existing string.

Sets `ErrCode_MEM` if heap-memory allocation fails.
******************************************************************************/
ScanBuf ScanBuf_new(char* data);


/******************************************************************************
Delete a `ScanBuf`.
******************************************************************************/
void ScanBuf_del(ScanBuf this);


/******************************************************************************
Advance the cursor of a `ScanBuf` one position forward.

Sets `ErrCode_BOUNDS` if the operation will result in the cursor being
out-of-bounds.
******************************************************************************/
void ScanBuf_adv(ScanBuf this);


/******************************************************************************
Return the character of a `ScanBuf` at the current cursor position.
******************************************************************************/
char ScanBuf_get(ScanBuf this);


/******************************************************************************
Return the character of a `ScanBuf` one position ahead of the cursor.

Sets `ErrCode_BOUNDS` and returns `-1` if the cursor is already at the final 
position in the buffer.
******************************************************************************/
char ScanBuf_peek(ScanBuf this);


#endif
