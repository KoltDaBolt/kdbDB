#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "input.h"
#include "error.h"

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

void print_logo_debug(void) {
    printf(" _       _ _     ____  ____            _      _                 \n");
    printf("| | ____| | |__ |  _ \\| __ )        __| | ___| |__  _   _  __ _ \n");
    printf("| |/ / _` | '_ \\| | | |  _ \\ _____ / _` |/ _ \\ '_ \\| | | |/ _` |\n");
    printf("|   < (_| | |_) | |_| | |_) |_____| (_| |  __/ |_) | |_| | (_| |\n");
    printf("|_|\\_\\__,_|_.__/|____/|____/       \\__,_|\\___|_.__/ \\__,_|\\__, |\n");
    printf("                                                          |___/ \n");
    printf("\n");
}

size_t visible_length(const char* str) {
    size_t len = 0;
    while (*str) {
        if (*str == '\033' && *(str + 1) == '[') {
            str += 2;
            while (*str && *str != 'm') {
                str++;
            }
            if (*str == 'm') str++;
        } else {
            len++;
            str++;
        }
    }

    return len;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        log_error(true, true, "This program does not accept command line arguments");
        return EXIT_INVALID_ARGS;
    }

    char* prompt = COLOR_BRIGHT_BLUE "kdbDB" COLOR_WHITE "@" COLOR_BRIGHT_GREEN "none" COLOR_WHITE "> ";
    size_t prompt_length = visible_length(prompt);
    char userInput[MAX_QUERY_LENGTH];
    InputStatus userInputStatus;

    printf(CLEAR_SCREEN CURSOR_START);

    #ifdef DEBUG
        print_logo_debug();
    #else
        print_logo();
    #endif

    for (;;) {
        printf("%s", prompt);
        
        userInputStatus = get_user_input(userInput, prompt_length);
        if (userInputStatus == INPUT_EOF) {
            printf("\n\nEOF\n\n");
            break;
        } else if (userInputStatus != INPUT_OK) {
            continue;
        }
    }

    return EXIT_SUCCESS;
}
