#include <stdio.h>

#include "vprint.h"
#include "terminal.h"

void clearScreen() {
    printf(CLEAR_SCREEN CURSOR_START);
}