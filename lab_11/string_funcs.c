#include <stdio.h>
#include "string_funcs.h"

#define MAX_INT_SIZE 22
#define SWAP(t, a, b) { t c = a; a = b; b = c; }

static void reverse_string(char *string, int length)
{
    for (int i = 0; i < length / 2; i++)
    {
        {
            SWAP(char, *(string - i - 1), *(string - length + i));
        }
    }
}

static int integer_to_string(char *string, long integer, const int base)
{
    int length = 0;
    bool is_negative = integer < 0 ? true : false;
    integer = labs(integer);

    do
    {
        ++length;
        *(string++) = (integer % base) + '0';
    } while (integer /= base);

    if (is_negative)
    {
        *string++ = '-';
        ++length;
    }

    reverse_string(string, length);

    return length;
}


void integer_into_string(char **buffer, long number, int *const size, const int maxsize, const int base)
{
    #ifdef DEBUG
        printf("%s: %s | %ld current number | %d | %d current size\n", __func__, *buffer, number, maxsize, *size);
    #endif

    char int_buffer[MAX_INT_SIZE];
    int number_length = integer_to_string(int_buffer, number, base);
    int buffer_ind = 0;

    for (; buffer_ind < number_length && *size < maxsize; buffer_ind++, (*size)++)
    {
        *((*buffer)++) = *(int_buffer + buffer_ind);
    }

    *size += (number_length - buffer_ind);
}
