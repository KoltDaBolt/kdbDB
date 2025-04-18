#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>

#include "token.h"

typedef enum {
    SCANNER_OK = 1
} ScannerStatus;

typedef struct {
    const char* queryStart;
    const char* start;
    const char* current;
} Scanner;

#ifdef DEBUG
    extern const char* tokenNames[];
#endif

void initScanner(const char*);
Token scanToken();
bool isAtEnd();
Token makeToken();
Token errorToken(const char*);
char advance();
bool match(char);
void skipWhitespace();
char peek();
char peekNext();
Token string();
bool isDigit(char);
Token number();
bool isAlpha(char);
Token identifier();
TokenType identifierType();
TokenType checkKeyword(int, int, const char*, TokenType);

#endif