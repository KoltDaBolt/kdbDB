#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "input.h"

InputStatus get_user_input(char* inputBuffer, size_t size) {
    if (fgets(inputBuffer, MAX_QUERY_LENGTH, stdin) == NULL) {
        if (feof(stdin)) {
            return INPUT_EOF;
        } else {
            log_error(true, true, "Failed to read from stdin.");
            return INPUT_ERROR;
        }
    }

    if (strchr(inputBuffer, '\n') == NULL) {
        log_error(true, true, "Input exceeds maximum length allowed");

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        return INPUT_TOO_LONG;
    }

    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

    return INPUT_OK;
}