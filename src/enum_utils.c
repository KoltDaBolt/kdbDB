#ifdef DEBUG

    #include "enum_utils.h"

    const char* tokenNames[] = {
        "TOKEN_LEFT_PAREN",
        "TOKEN_RIGHT_PAREN",
        "TOKEN_COMMA",
        "TOKEN_PLUS",
        "TOKEN_MINUS",
        "TOKEN_STAR",
        "TOKEN_SLASH",
        "TOKEN_MOD",
        "TOKEN_SEMICOLON",
        "TOKEN_EQUAL",
        "TOKEN_GREATER",
        "TOKEN_GREATER_EQUAL",
        "TOKEN_LESS",
        "TOKEN_LESS_EQUAL",
        "TOKEN_IDENTIFIER",
        "TOKEN_STRING",
        "TOKEN_NUMBER",
        "TOKEN_CREATE",
        "TOKEN_CLEAR",
        "TOKEN_DATABASE",
        "TOKEN_LIST",
        "TOKEN_USE",
        "TOKEN_END",
        "TOKEN_ERROR"
    };

    const char* parserStateNames[] = {
        "PARSER_STATE_READY",
        "PARSER_STATE_SAW_LIST",
        "PARSER_STATE_SAW_CREATE",
        "PARSER_STATE_CREATE_DATABASE_EXPECTING_IDENTIFIER",
        "PARSER_STATE_CREATE_DATABASE_RECEIVED_IDENTIFIER",
        "PARSER_STATE_CLEAR",
        "PARSER_STATE_LIST_DATABASE",
        "PARSER_STATE_COMPLETE"
    };

    const char* enumToString(EnumType enumeration, int entry) {
        switch (enumeration) {
            case ENUM_TOKEN_TYPE:
                return tokenNames[entry];
            case ENUM_PARSER_STATE:
                return parserStateNames[entry];
            default:
                return "enum_utils error";
        }

        return "enum_utils error";
    }
#endif