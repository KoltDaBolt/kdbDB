#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "query.h"

typedef enum {
    PARSER_STATE_READY = 0,
    PARSER_STATE_SAW_LIST,
    PARSER_STATE_SAW_CREATE,
    PARSER_STATE_CREATE_DATABASE_EXPECTING_IDENTIFIER,
    PARSER_STATE_CREATE_DATABASE_RECEIVED_IDENTIFIER,
    PARSER_STATE_CLEAR,
    PARSER_STATE_LIST_DATABASE,
    PARSER_STATE_COMPLETE
} ParserState;

typedef enum {
    PARSER_STATUS_OK,
    PARSER_STATUS_SYNTAX_ERROR,
    PARSER_STATUS_ALLOCATION_FAILED,
    PARSER_STATUS_ALLOCATION_SUCCESS,    
    PARSER_STATUS_INVALID_STATE
} ParserStatus;

typedef struct {
    ParserState state;
    TokenType previousToken;
} Parser;

void initParser();
void setPreviousToken(TokenType);
ParserStatus doAllocation(Query*, Token);
void freeQuery(Query*);
ParserStatus parseToken(Query*, Token);

#endif