// Copyright (C) 2024  KA Wright

/******************************************************************************
tokbuf.c - Token buffer implementation
******************************************************************************/

#include <stdlib.h>

#include "err.h"
#include "tok.h"
#include "tokbuf.h"

/******************************************************************************
__TOK_BUF__
******************************************************************************/
struct __TOK_BUF__ {
    Tok *toks;
    long len;
    long curs;
};

/******************************************************************************
TokBuf_new
******************************************************************************/
TokBuf TokBuf_new() {
    TokBuf ret = malloc(sizeof(struct __TOK_BUF__));
    if (ret == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Couldn't allocate token buffer");
        return NULL;
    }

    ret->toks = NULL;
    ret->len = 0;
    ret->curs = 0;
    
    return ret;
}

/******************************************************************************
TokBuf_del
******************************************************************************/
void TokBuf_del(TokBuf this) {
    for (int i=0; i<this->len; i++) {
        Tok_del(this->toks[i]);
    }
    free(this);
}


/******************************************************************************
TokBuf_push
******************************************************************************/
void TokBuf_push(TokBuf this, Tok val) {
    this->len++;
    if (this->len == 1) {
        this->toks = malloc(sizeof(Tok));
        if (this->toks == NULL) {
            ErrState_setCode(ErrCode_MEM);
            ErrState_setMsg("Couldn't allocate token buffer");
            return;
        }
    } else {
        this->toks = realloc(this->toks, sizeof(Tok) * this->len);
        if (this->toks == NULL) {
            ErrState_setCode(ErrCode_MEM);
            ErrState_setMsg("Couldn't allocate token buffer");
            return;
        }
    }
    this->toks[this->len - 1] = val;
    return;
}


/******************************************************************************
TokBuf_adv
******************************************************************************/
void TokBuf_adv(TokBuf this) {
    if (this->curs >= (this->len - 1)) {
        ErrState_setCode(ErrCode_BOUNDS);
        ErrState_setMsg("End of buffer reached");
        return;
    }
    this->curs++;
}


/******************************************************************************
TokBuf_get
******************************************************************************/
Tok TokBuf_get(TokBuf this) {
    return this->toks[this->curs];
}


/******************************************************************************
TokBuf_peek
******************************************************************************/
Tok TokBuf_peek(TokBuf this) {
    if (this->curs >= (this->len - 1)) {
        ErrState_setCode(ErrCode_BOUNDS);
        ErrState_setMsg("End of buffer reached");
        return NULL;
    }
    return this->toks[this->curs + 1];
}

