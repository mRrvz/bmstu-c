#include <stdlib.h>
#include "arr_oper.h"

#define OK 0
#define REALLOC_ERR 7

#define EPS 1e-9

void *memory_changer(double *const *const arr, const short int new_n, short int *const code_err, double **const arr_end)
{
    double *new_arr = NULL;
    new_arr = realloc(*arr, new_n * sizeof(double));

    if (new_arr == NULL)
    {
        *code_err = REALLOC_ERR;
        return *arr;
    }
    
    *arr_end = new_arr + new_n;
    *code_err = OK;

    return new_arr;
}

static void del_by_pos(double *const arr_end, double *const pos)
{
    for (double *i = pos; i < arr_end - 1; i++)
    {
        *i = *(i + 1);
    }
}

void *del_from_arr(double *const arr, double *arr_end, const double num1, short int *const n)
{
    for (double *i = arr; i < arr_end; i++)
    {
        if (num1 + EPS < *i)
        {
            del_by_pos(arr_end, i);
            --i;
            --arr_end;
        }
    }
    
    *n = arr_end - arr;

    return arr_end;
}

static void *add_by_pos(double *const arr, double *arr_end, double *const pos, const double added_numb)
{
    for (double *i = arr_end - 1; i >= pos; i--)
    {
        *(i + 1) = *i;
    }

    *pos = added_numb;

    return ++arr_end;
}

void add_to_arr(double *arr, double *arr_end, double *const pos, const double num2)
{
    arr_end = add_by_pos(arr, arr_end, pos, num2);
    arr_end = add_by_pos(arr, arr_end, arr, num2);
    arr_end = add_by_pos(arr, arr_end, arr_end, num2);
} 

