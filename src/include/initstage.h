// Copyright (C) 2024  KA Wright

/******************************************************************************
initstage.h - Initialization stages
******************************************************************************/

/******************************************************************************
Lists all initialization stages.
******************************************************************************/
typedef enum {
    InitStage_BEGIN,
    InitStage_ARGVPARSE_LOAD,
    InitStage_SCANBUF_LOAD,
    InitStage_LEX_DONE
} InitStage; 

