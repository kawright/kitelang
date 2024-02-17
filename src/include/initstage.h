// Copyright (C) 2024  KA Wright

/******************************************************************************
initstage.h - Initialization stages
******************************************************************************/

// TODO Add new init stage InitStage_LEX_DONE

/******************************************************************************
Lists all initialization stages.
******************************************************************************/
typedef enum {
    InitStage_BEGIN,
    InitStage_ARGVPARSE_LOAD,
    InitStage_SCANBUF_LOAD
} InitStage; 

