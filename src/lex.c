// Copyright (C) 2024  KA Wright

/******************************************************************************
lex.c - Implementation of lexer API
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "lex.h"
#include "scanbuf.h"
#include "tok.h"

int __endReached__ = 0;

// PRIVATE FUNCTIONS

/******************************************************************************
Scan a quoted string and return it (without the quotes).

Sets `ErrCode_BOUNDS` and returns `NULL`  if the end of the buffer is reached 
before the string is closed.

Sets `ErrCode_MEM` and returns `NULL` if heap-memory allocation fails.
******************************************************************************/
char *__scanStr__(char delim, ScanBuf buf) {
    long retlen = 0;
    char *ret = malloc(retlen + 1);
    if (ret == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Couldn't allocate scanned string");
        return NULL;
    }
    ret[0] = '\0';
    
    ScanBuf_adv(buf);
    if (ErrState_getCode() == ErrCode_BOUNDS) {
        ErrState_setMsg("Unclosed string detected");
        free(ret);
        return NULL;
    }
    char curr = ScanBuf_get(buf);
    
    while (curr != delim) {
        retlen++;
        ret = realloc(ret, retlen + 1);
        if (ret == NULL) {
            ErrState_setCode(ErrCode_MEM);
            ErrState_setMsg("Couldn't allocate scanned string");
            return NULL;
        }
        ret[retlen - 1] = curr;
        
        ScanBuf_adv(buf);
        if (ErrState_getCode() == ErrCode_BOUNDS) {
            ErrState_setMsg("Unclosed string detected");
            free(ret);
            return NULL;
        }
        curr = ScanBuf_get(buf);
    }
    return ret;
}   

/******************************************************************************
Test if a given character is present in a given string.
******************************************************************************/
int __inStr__(char testChar, char *testStr) {
    for (int i=0; i<strlen(testStr); i++) {
        if (testChar == testStr[i]) {
            return 1;
        }
    }
    return 0;
}

/******************************************************************************
Scan the buffer until a non-legal character is encountered, then return the
scanned string.

Sets `ErrCode_MEM` and returns `NULL` if heap-memory allocation fails.
******************************************************************************/
char *__scan__(char first, char* legal, ScanBuf buf) {
    long retlen = 1;
    char *ret = malloc(retlen + 1);
    if (ret == NULL) {
        ErrState_setCode(ErrCode_MEM);
        ErrState_setMsg("Couldn't allocate scanned string");
        return NULL;
    }
    ret[0] = first;
    ret[1] = '\0';
    
    ScanBuf_adv(buf);
    if (ErrState_getCode() == ErrCode_BOUNDS) {
        ErrState_reset();
        return ret;
    }
    char curr = ScanBuf_get(buf);

    while (ErrState_getCode() != ErrCode_BOUNDS && __inStr__(curr, legal)) {
        retlen++;
        ret = realloc(ret, retlen + 1);
        if (ret == NULL) {
            ErrState_setCode(ErrCode_MEM);
            ErrState_setMsg("Couldn't allocate scanned string");
            free(ret);
            return NULL;
        }
        ret[retlen - 1] = curr;
        ScanBuf_adv(buf);   
    }
    if (ErrState_getCode() == ErrCode_BOUNDS) {
        ErrState_reset();
    }
    return ret;
}

// PUBLIC FUNCTIONS

/******************************************************************************
Lex_next
******************************************************************************/
Tok Lex_next(ScanBuf buf) {
    Tok ret;
    if (__endReached__) {
        ret = Tok_new(TokType_END, NULL);
        if (ErrState_getCode() == ErrCode_MEM) {
            return NULL;
        }
        return ret; 
    }

    char curr = ScanBuf_get(buf);
    while (ErrState_getCode() != ErrCode_BOUNDS) {
        switch (curr) {
            
            // WHITESPACE:
            case ' ':
            case '\n':
            case '\r':
            case '\t':
                continue;
            
            // SPECIAL CHARACTER:
            case '(':
            case ')':
            case '{':
            case '}':
            case ',':
            case ';':
            case '=':
            case ':':
                char specTokVal[2];
                specTokVal[0] = curr;
                specTokVal[1] = '\0';
                ret = Tok_new(TokType_SPEC, specTokVal);
                if (ErrState_getCode() == ErrCode_MEM) {
                    return NULL;
                }
                return ret;
            
            // STRING:
            case '"':
            case '\'':
                char *strTokVal;
                strTokVal = __scanStr__(curr, buf);
                if (ErrState_getCode() != ErrCode_OK) {
                    return NULL;
                }
                ret = Tok_new(TokType_STR, strTokVal);
                if (ErrState_getCode() == ErrCode_MEM) {
                    return NULL;
                }
                return ret;

            // NAME:
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case '_':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                char *nameTokVal;
                char legal[] =  "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "0123456789_";
                nameTokVal = __scan__(curr, legal, buf);
                if (ErrState_getCode() != ErrCode_OK) {
                    return NULL;
                }
                ret = Tok_new(TokType_NAME, nameTokVal);
                if (ErrState_getCode() == ErrCode_MEM) {
                    return NULL;
                }
                return ret;

            default:
                ErrState_setCode(ErrCode_ILLEGAL);
                ErrState_setMsg("Illegal character found");
                return NULL;
        }
        ScanBuf_adv(buf);
        curr = ScanBuf_get(buf);
    }

    if (ErrState_getCode() == ErrCode_BOUNDS) {
        ErrState_reset();
    }

    __endReached__ = 1;
    ret = Tok_new(TokType_END, NULL);   
    if (ErrState_getCode() == ErrCode_MEM) {
        return NULL;
    }
    return ret;
}
