#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "input.h"

typedef enum {
    EXIT_SUCCESS = 0,
    EXIT_INVALID_ARGS,
} ExitStatus;

void print_logo(void) {
    printf(" _       _ _     ____  ____  \n");
    printf("| | ____| | |__ |  _ \\| __ ) \n");
    printf("| |/ / _` | '_ \\| | | |  _ \\ \n");
    printf("|   < (_| | |_) | |_| | |_) |\n");
    printf("|_|\\_\\__,_|_.__/|____/|____/ \n");
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc > 1) {
        log_error(true, true, "This program does not accept command line arguments");
        return EXIT_INVALID_ARGS;
    }

    char userInput[MAX_QUERY_LENGTH];
    InputStatus userInputStatus;

    printf(CLEAR_SCREEN CURSOR_START);
    print_logo();
    for (;;) {
        printf(COLOR_BRIGHT_BLUE "kdbDB" COLOR_WHITE "@" COLOR_BRIGHT_GREEN "none" COLOR_WHITE "> ");
        
        userInputStatus = get_user_input(userInput);
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
