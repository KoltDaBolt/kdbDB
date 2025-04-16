#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

#define MAX_QUERY_LENGTH 1000

typedef enum {
    INPUT_OK = 0,
    INPUT_ERROR,
    INPUT_TOO_LONG,
    INPUT_EOF,
} InputStatus;

InputStatus getUserInput(char* inputBuffer, size_t prompt_length);

#endif