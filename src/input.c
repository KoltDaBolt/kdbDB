#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "input.h"
#include "error.h"

InputStatus getUserInput(char* inputBuffer, size_t prompt_length) {
    size_t line_offset = 0;

    while (1) {
        if (line_offset > 0) {
            printf("%*s ", (int)prompt_length, "...> ");
        }

        if (fgets(inputBuffer + line_offset, MAX_QUERY_LENGTH - line_offset, stdin) == NULL) {
            if (feof(stdin)) {
                return INPUT_EOF;
            } else {
                log_error(true, true, "Failed to read from stdin.");
                return INPUT_ERROR;
            }
        }

        if (strchr(inputBuffer + line_offset, '\n') == NULL) {
            log_error(true, true, "Input exceeds maximum length allowed");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

            return INPUT_TOO_LONG;
        }

        size_t current_line_length = strlen(inputBuffer + line_offset);

        if (current_line_length > 0 && inputBuffer[line_offset + current_line_length - 2] != ';') {
            inputBuffer[line_offset + current_line_length - 1] = ' ';
            line_offset += current_line_length;
            continue;
        } else {
            inputBuffer[line_offset + current_line_length - 1] = '\0';
            break;
        }

        break;
    }

    #ifdef DEBUG
        printf("\n");
        printf("-=-=-=-=-= input.c:getUserInput() =-=-=-=-=-\n");
        printf("Size of user input buffer: %u\n", MAX_QUERY_LENGTH);
        printf("Length of actual input:    %zu\n", strlen(inputBuffer));
        printf("User Input: %s\n", inputBuffer);
        printf("\n");
    #endif

    return INPUT_OK;
}