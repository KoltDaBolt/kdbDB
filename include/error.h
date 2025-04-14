#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

void log_error(bool marginTop, bool marginBottom, const char* format, ...);
void log_warning(bool marginTop, bool marginBottom, const char* format, ...);

#endif