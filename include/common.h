#ifndef COMMON_H
#define COMMON_H

#define COLOR_RESET         "\033[0m"
#define COLOR_RED           "\033[31m"
#define COLOR_BRIGHT_GREEN  "\033[92m"
#define COLOR_YELLOW        "\033[33m"
#define COLOR_BRIGHT_BLUE   "\033[94m"
#define COLOR_WHITE         "\033[37m"

#define CLEAR_SCREEN        "\033[2J"
#define CURSOR_START        "\033[H"

#define MAX_QUERY_LENGTH 1000

#include <stdbool.h>

void log_error(bool marginTop, bool marginBottom, const char* format, ...);
void log_warning(bool marginTop, bool marginBottom, const char* format, ...);

#endif