#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

typedef enum {
    INPUT_OK = 0,
    INPUT_ERROR,
    INPUT_TOO_LONG,
    INPUT_EOF,
} InputStatus;

InputStatus get_user_input(char* inputBuffer);

#endif