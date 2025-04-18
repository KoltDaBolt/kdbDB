#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_LEFT_PAREN = 0,   // Single Character Tokens
    TOKEN_RIGHT_PAREN,
    TOKEN_COMMA,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_MOD,
    TOKEN_SEMICOLON,
    TOKEN_EQUAL,
    TOKEN_GREATER,          // One or Two Character Tokens
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_IDENTIFIER,       // Literals
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_CREATE,           // Keywords
    TOKEN_CLEAR,
    TOKEN_DATABASE,
    TOKEN_LIST,
    TOKEN_USE,
    TOKEN_END,              // End
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
    int column;
} Token;

#endif

/* Tokens to add later
    TOKEN_TABLE,
    TOKEN_SELECT,
    TOKEN_INSERT,
    TOKEN_UPDATE,
    TOKEN_DELETE,
    TOKEN_FROM,
    TOKEN_WHERE,
    TOKEN_VALUES,
    TOKEN_LIMIT,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_PRIMARY_KEY,
    TOKEN_UNIQUE,
    TOKEN_ORDER_BY,
    TOKEN_ASC,
    TOKEN_DESC,
*/