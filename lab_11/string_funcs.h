#ifndef __STR_FUNCS_H__
#define __STR_FUNCS_H__

#include <stdlib.h>

typedef enum boolean
{
    false = 0,
    true = 1
} bool;

void integer_into_string(char **buffer, long number, int *const size, const int maxsize, const int base);

#endif
