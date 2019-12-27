#include <stdlib.h>
#include <stdarg.h>

#include "parsing.h"
#include "snprintf.h"

int my_snprintf(char *buffer, size_t size, char *format, ...)
{
    va_list arguments_ptr;
    va_start(arguments_ptr, format);
    int buffer_size = 0;

    do
    {
        if (*format == '%')
        {
            add_argument(&format, &buffer, &buffer_size, size, arguments_ptr);
        }
        else if (buffer_size++ < size)
        {
            *(buffer++) = *format;
        }
    } while (*format++);

    if (size)
    {
        *(buffer - 1) = '\0';
    }

    va_end(arguments_ptr);

    return --buffer_size;
}
