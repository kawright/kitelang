// Copyright (C) 2024  KA Wright

/******************************************************************************
scanbuf.c - Implementation of a scannable buffer which supports look-ahead.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "scanbuf.h"

struct __SCAN_BUFFER__ {
    char* data;
    long len;
    long curs;
};

ScanBuffer ScanBuffer_new(char* data) {
    ScanBuffer ret = malloc(sizeof(struct __SCAN_BUFFER__));
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

void ScanBuffer_del(ScanBuffer this) {
    free(this->data);
    free(this);
}

void ScanBuffer_adv(ScanBuffer this) {
    if (this->curs >= (this->len-1)) {
        ErrState_setCode(ErrCode_BOUNDS);
        ErrState_setMsg("End of buffer reached");
        return;
    }
    this->curs++;
}

char ScanBuffer_get(ScanBuffer this) {
    return this->data[this->curs];
}

char ScanBuffer_peek(ScanBuffer this) {
    
    if (this->curs >= (this->len-1)) {
        ErrState_setCode(ErrCode_BOUNDS);
        ErrState_setMsg("End of buffer reached");
        return -1;
    }
    return this->data[this->curs+1];
}
