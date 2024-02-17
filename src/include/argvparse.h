// Copyright (C) 2024  KA Wright

/******************************************************************************
argvparse.h - Argument vector parsing API
******************************************************************************/

#ifndef __ARGVPARSE_H__
#define __ARGVPARSE_H__


/******************************************************************************
Opaque handle to the result of parsing the argument vector.
******************************************************************************/
typedef struct __ARGV_PARSE__ *ArgvParse;


/******************************************************************************
Create a new `ArgvParse`.

Sets `ErrCode_MEM` if heap-memory allocation fails.

Sets `ErrCode_ARGV` if the argument vector is malformed.
******************************************************************************/
ArgvParse ArgvParse_new(int argc, char *argv[]);


/******************************************************************************
Delete an `ArgvParse`.
******************************************************************************/
void ArgvParse_del(ArgvParse this);


/******************************************************************************
Get the filename from an `ArgvParse`.
******************************************************************************/
char *ArgvParse_getFile(ArgvParse this);


/******************************************************************************
Get whether or not the `-l` or `--lex-only` option was given.
******************************************************************************/
int ArgvParse_getIsLexOnly(ArgvParse this);


#endif

