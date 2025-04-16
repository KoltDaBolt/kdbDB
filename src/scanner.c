#include <string.h>

#include "scanner.h"

#ifdef DEBUG
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
#endif

Scanner scanner;

void initScanner(const char* query) {
    scanner.queryStart = query;
    scanner.start = query;
    scanner.current = query;
}

Token scanToken() {
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_END);

    char c = advance();

    if (isAlpha(c)) return identifier();
    if (isDigit(c)) return number();

    switch (c) {
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case ',': return makeToken(TOKEN_COMMA);
        case '+': return makeToken(TOKEN_PLUS);
        case '-': return makeToken(TOKEN_MINUS);
        case '*': return makeToken(TOKEN_STAR);
        case '/': return makeToken(TOKEN_SLASH);
        case '%': return makeToken(TOKEN_MOD);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case '=': return makeToken(TOKEN_EQUAL);
        case '>': return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '<': return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '"': return string();
    }

    return errorToken("ERROR: Unexpected token");
}

bool isAtEnd() {
    return *scanner.current == '\0';
}

Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.column = (int)(scanner.start - scanner.queryStart) + 1;
    return token;
}

Token errorToken(const char* msg) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = msg;
    token.length = (int)strlen(msg);
    token.column = (int)(scanner.start - scanner.queryStart) + 1;
    return token;
}

char advance() {
    scanner.current++;
    return scanner.current[-1];
}

bool match(char expected) {
    if (isAtEnd()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

void skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            default:
                return;
        }
    }
}

char peek() {
    return *scanner.current;
}

char peekNext() {
    if (isAtEnd()) return '\0';
    return scanner.current[1];
}

Token string() {
    while (peek() != '"' && !isAtEnd()) {
        advance();
    }

    if (isAtEnd()) return errorToken("ERROR: Unterminated string");

    advance();
    return makeToken(TOKEN_STRING);
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

Token number() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
    }

    return makeToken(TOKEN_NUMBER);
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

Token identifier() {
    while (isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}

TokenType identifierType() {
    switch (scanner.start[0]) {
        case 'c': 
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'l': return checkKeyword(2, 3, "ear", TOKEN_CLEAR);
                    case 'r': return checkKeyword(2, 4, "eate", TOKEN_CREATE);
                }
            }
        case 'd': return checkKeyword(1, 7, "atabase", TOKEN_DATABASE);
        case 'l': return checkKeyword(1, 3, "ist", TOKEN_LIST);
        case 'u': return checkKeyword(1, 2, "se", TOKEN_USE);
    }

    return TOKEN_IDENTIFIER;
}

TokenType checkKeyword(int start, int length, const char* rest, TokenType type) {
    if (scanner.current - scanner.start == start + length &&
        memcmp(scanner.start + start, rest, length) == 0) {
        return type;
    }

    return TOKEN_IDENTIFIER;
}