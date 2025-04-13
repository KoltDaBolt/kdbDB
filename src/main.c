#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "input.h"

typedef enum {
    EXIT_SUCCESS = 0,
    EXIT_INVALID_ARGS,
} ExitStatus;

int main(int argc, char** argv) {
    if (argc > 1) {
        log_error(true, true, "This program does not accept command line arguments");
        return EXIT_INVALID_ARGS;
    }

    char userInput[MAX_QUERY_LENGTH];
    InputStatus userInputStatus;

    printf(CLEAR_SCREEN CURSOR_START);
    for (;;) {
        printf(COLOR_BRIGHT_BLUE "kdbDB" COLOR_WHITE "@" COLOR_BRIGHT_GREEN "none" COLOR_WHITE "> ");
        
        userInputStatus = get_user_input(userInput, MAX_QUERY_LENGTH);
        if (userInputStatus == INPUT_EOF) {
            printf("\n\nEOF\n\n");
            break;
        } else if (userInputStatus != INPUT_OK) {
            continue;
        }

        printf("\n");
        printf("Size of user input buffer: %zu\n", sizeof(userInput));
        printf("Length of actual input:    %zu\n", strlen(userInput));
        printf("User Input: %s\n", userInput);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
