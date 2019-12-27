#include "math_oper.h"

#define EPS 1e-9

void num1_calc(double *const num1, double *const arr, const double *const arr_end)
{
    for (double *i = arr; i < arr_end; i++)
    {
        *num1 += *i;
    }

    *num1 /= (arr_end - arr);
}

void num2_calc(double *const num2, double *const arr, const double *const arr_end)
{
    *num2 = *arr;

    for (double *i = arr; i < arr_end; i++)
    {
        if (*num2 + EPS < *i)
        {
            *num2 = *i;
        }
    }
}

