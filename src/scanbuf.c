// Copyright (C) 2024  KA Wright

/******************************************************************************
scanbuf.c - Implementation of a scannable buffer which supports look-ahead.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "scanbuf.h"

/******************************************************************************
__SCAN_BUF__
******************************************************************************/
struct __SCAN_BUF__ {
    char* data;
    long len;
    long curs;
};

/******************************************************************************
ScanBuf_new
******************************************************************************/
ScanBuf ScanBuf_new(char* data) {
    ScanBuf ret = malloc(sizeof(struct __SCAN_BUF__));
    if (ret == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Cannot allocate `ScanBuffer`");
        return NULL;
    }
    
    ret->len = strlen(data);
    ret->curs = 0;
    
    ret->data = malloc(ret->len + 1);
    if (ret->data == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Cannot allocate `ScanBuffer` data");
        free(ret);
        return NULL;
    }
    
    strcpy(ret->data, data);

    return ret;
}

/******************************************************************************
ScanBuf_del
******************************************************************************/
void ScanBuf_del(ScanBuf this) {
    free(this->data);
    free(this);
}

/******************************************************************************
ScanBuf_adv
******************************************************************************/
void ScanBuf_adv(ScanBuf this) {
    if (this->curs >= (this->len-1)) {
        ErrState_setCode(ErrCode_BOUNDS);
        ErrState_setMsg("End of buffer reached");
        return;
    }
    this->curs++;
}

/******************************************************************************
ScanBuf_get
******************************************************************************/
char ScanBuf_get(ScanBuf this) {
    return this->data[this->curs];
}

/******************************************************************************
ScanBuf_peek
******************************************************************************/
char ScanBuf_peek(ScanBuf this) {
    
    if (this->curs >= (this->len-1)) {
        ErrState_setCode(ErrCode_BOUNDS);
        ErrState_setMsg("End of buffer reached");
        return -1;
    }
    return this->data[this->curs+1];
}
