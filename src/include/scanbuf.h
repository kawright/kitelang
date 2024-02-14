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
typedef struct __SCAN_BUFFER__ *ScanBuffer;


/******************************************************************************
Create a new `ScanBuffer` from an existing string.

Sets `ErrCode_MEM` if heap-memory allocation fails.
******************************************************************************/
ScanBuffer ScanBuffer_new(char* data);


/******************************************************************************
Delete a `ScanBuffer`.
******************************************************************************/
void ScanBuffer_del(ScanBuffer this);


/******************************************************************************
Advance the cursor one position forward.

Sets `ErrCode_BOUNDS` if the operation will result in the cursor being
out-of-bounds.
******************************************************************************/
void ScanBuffer_adv(ScanBuffer this);


/******************************************************************************
Return the character at the given cursor position.
******************************************************************************/
char ScanBuffer_get(ScanBuffer this);


/******************************************************************************
Return the character one position ahead of the cursor.

Sets `ErrCode_BOUNDS` and returns `-1` if the cursor is already at the final 
position in the buffer.
******************************************************************************/
char ScanBuffer_peek(ScanBuffer this);


#endif
