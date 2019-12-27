#include <stdio.h>
#include "print.h"

void print_result(double *const arr, const double *const arr_end)
{
    for (double *i = arr; i < arr_end; i++)
    {
        printf("%lf ", *i);
    }

    printf("\n");
}
