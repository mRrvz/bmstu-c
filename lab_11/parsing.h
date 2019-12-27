#ifndef __PARSING_H__
#define __PARSING_H__

#include <stdlib.h>

void add_argument(char **format, char **buffer, int *const size, const int maxsize, va_list args);

#endif
