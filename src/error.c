#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "common.h"
#include "error.h"

void log_error(bool marginTop, bool marginBottom, const char* format, ...) {
    if (marginTop) printf("\n");

    printf(COLOR_RED "ERROR: ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf(COLOR_RESET);

    if (marginBottom) printf("\n");
    printf("\n");
}

void log_warning(bool marginTop, bool marginBottom, const char* format, ...) {
    if (marginTop) printf("\n");

    printf(COLOR_YELLOW "WARNING: ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf(COLOR_RESET);

    if (marginBottom) printf("\n");
    printf("\n");
}
