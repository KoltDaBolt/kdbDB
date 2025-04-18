#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "enum_utils.h"

Parser parser;

void initParser() {
    parser.state = PARSER_STATE_READY;
}

void setPreviousToken(TokenType type) {
    parser.previousToken = type;
}

ParserStatus doAllocation(Query* query, Token token) {
    char* allocation = (char*)malloc(token.length + 1);
    if (allocation == NULL) {
        return PARSER_STATUS_ALLOCATION_FAILED;
    }

    query->data.createDbQuery.dbname = allocation;
    memcpy((char*)query->data.createDbQuery.dbname, token.start, token.length);
    ((char*)query->data.createDbQuery.dbname)[token.length] = '\0';
    return PARSER_STATUS_ALLOCATION_SUCCESS;
}

void freeQuery(Query* query) {
    switch (query->type) {
        case QUERY_TYPE_CREATE_DATABASE:
            free((char*)query->data.createDbQuery.dbname);
            break;
        default:
            return;
    }
}

ParserStatus parseToken(Query* query, Token token) {
    #ifdef DEBUG
        printf("\n");
        printf("-=-=-=-=-= parser.c:parseToken() =-=-=-=-=-\n");
        printf("Previous parser state: %s\n", enumToString(ENUM_PARSER_STATE, parser.state));
        printf("Token type: %s\n", enumToString(ENUM_TOKEN_TYPE, token.type));
    #endif

    switch (parser.state) {
        case PARSER_STATE_READY:
            if (token.type == TOKEN_CLEAR) {
                setPreviousToken(token.type);
                parser.state = PARSER_STATE_CLEAR;
                query->type = QUERY_TYPE_CLEAR;
                break;
            } else if (token.type == TOKEN_LIST) {
                setPreviousToken(token.type);
                parser.state = PARSER_STATE_SAW_LIST;
                break;
            } else if (token.type == TOKEN_CREATE) {
                setPreviousToken(token.type);
                parser.state = PARSER_STATE_SAW_CREATE;
                break;
            } else {
                return PARSER_STATUS_SYNTAX_ERROR;
            }
        
        case PARSER_STATE_SAW_LIST:
            if (token.type == TOKEN_DATABASE) {
                setPreviousToken(token.type);
                parser.state = PARSER_STATE_LIST_DATABASE;
                query->type = QUERY_TYPE_LIST_DATABASE;
                break;
            } else {
                return PARSER_STATUS_SYNTAX_ERROR;
            }

        case PARSER_STATE_SAW_CREATE:
            if (token.type == TOKEN_DATABASE) {
                setPreviousToken(token.type);
                parser.state = PARSER_STATE_CREATE_DATABASE_EXPECTING_IDENTIFIER;
                query->type = QUERY_TYPE_CREATE_DATABASE;
                break;
            } else {
                return PARSER_STATUS_SYNTAX_ERROR;
            }

        case PARSER_STATE_CREATE_DATABASE_EXPECTING_IDENTIFIER:
            if (token.type == TOKEN_IDENTIFIER) {
                setPreviousToken(token.type);
                parser.state = PARSER_STATE_CREATE_DATABASE_RECEIVED_IDENTIFIER;
                ParserStatus allocationStatus = doAllocation(query, token);
                if (allocationStatus == PARSER_STATUS_ALLOCATION_FAILED) return allocationStatus;
                break;
            } else {
                return PARSER_STATUS_SYNTAX_ERROR;
            }
        
        case PARSER_STATE_CLEAR:
        case PARSER_STATE_LIST_DATABASE:
        case PARSER_STATE_CREATE_DATABASE_RECEIVED_IDENTIFIER:
            if (token.type == TOKEN_SEMICOLON) {
                setPreviousToken(token.type);
                parser.state = PARSER_STATE_COMPLETE;
                break;
            } else {
                return PARSER_STATUS_SYNTAX_ERROR;
            }

        default:
            return PARSER_STATUS_INVALID_STATE;
    }

    #ifdef DEBUG
        printf("Updated parser state: %s\n", enumToString(ENUM_PARSER_STATE, parser.state));
    #endif

    return PARSER_STATUS_OK;
}