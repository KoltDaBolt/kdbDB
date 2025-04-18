#ifdef DEBUG

#ifndef ENUM_UTILS_H
#define ENUM_UTILS_H

typedef enum {
    ENUM_TOKEN_TYPE,
    ENUM_PARSER_STATE
} EnumType;

const char* enumToString(EnumType, int);

#endif

#endif