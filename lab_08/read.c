#include <stdlib.h>
#include <stdio.h>

#include "read.h"

#define OK 0
#define SIZE_ERR 1
#define INVALID_SIZE 2
#define ELEM_ERR 3
#define POS_ERR 4
#define INVALID_P 5
#define INVALID_MMRY 6

#define READ_OK 1

static void *init_arr(double **const arr, const short int n, short int *const code_err)
{
    *arr = calloc(n, sizeof(double));

    if (*arr == NULL)
    {
        *code_err = INVALID_MMRY;
        return NULL;
    }
    
    *code_err = OK;
    return *arr;
}

static int check_size(const short int n)
{
    if (n <= 0)
    {
        return INVALID_SIZE;
    }

    return OK;
}

static void arr_end_calc(double **const arr_end, double **const arr, const short int n)
{
    *arr_end = *arr + n;
}

int read_array(double **const arr, short int *const n, double **const arr_end)
{
    puts("Enter size of array: ");
    if (scanf("%hi", n) != READ_OK)
    {
        return SIZE_ERR;
    }

    if (check_size(*n))
    {
        return INVALID_SIZE;
    }

    short int code_err = 0;
    *arr = init_arr(arr, *n, &code_err);

    if (code_err)
    {
        return INVALID_MMRY;
    }

    arr_end_calc(arr_end, arr, *n);

    puts("Enter elements of array: ");
    for (double *i = *arr; i < *arr_end; i++)
    {
        if (scanf("%lf", i) != READ_OK)
        {
            return ELEM_ERR;
        }
    }

    return OK;
}

static int check_arr_entries(const short int *const pos, const short int n)
{
    if (*pos > (n - 1) || *pos < 0)
    {
        return INVALID_P;
    }
    
    return OK;
}

int read_number(short int *const pos, const short int n)
{
    puts("Enter number P: ");

    if (scanf("%hi", pos) != READ_OK)
    {
        return POS_ERR;
    }

    if (check_arr_entries(pos, n))
    {
        return INVALID_P;
    }

    return OK;
}

