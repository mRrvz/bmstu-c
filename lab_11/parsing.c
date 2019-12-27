#include <stdarg.h>
#include <stdio.h>

#include "parsing.h"
#include "string_funcs.h"

#define ITOS(type) integer_into_string(buffer, va_arg(args, type), size, maxsize, base)

void add_argument(char **format, char **buffer, int *const size, const int maxsize, va_list args)
{
    bool is_long = (*(++(*format)) == 'l') ? true : false;
    int base = 10;
    is_long ? (*format)++ : *format;

    #ifdef DEBUG
        printf("%s: %s | %s | %d | %d | %d\n", __func__,
            *format, *buffer, *size, is_long, maxsize);
    #endif

    switch (**format)
    {
        case 'd':
            is_long ? ITOS(long) : ITOS(int);
            break;
        case 'i':
            is_long ? ITOS(long) : ITOS(int);
            break;
        case 'o':
            base = 8;
            is_long ? ITOS(long unsigned) : ITOS(unsigned);
            break;
        default:
            if (++(*size) < maxsize)
            {
                *(*buffer)++ = '%';
                *format = **format != '%' ? (*format) - 1 : *format;
            }
    }

    #ifdef DEBUG
        printf("%s: %s | %s | %d | %d | %d\n", __func__,
            *format, *buffer, *size, is_long, maxsize);
    #endif
}
