#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "math_oper.h"
#include "arr_oper.h"
#include "print.h"

#define EXTRA_PLACES 3
#define OK 0

int main(void)
{
    setbuf(stdout, NULL);

    double *arr = NULL;
    double *arr_end = NULL;
    short int n = 0, p = 0;
    double num1 = 0, num2 = 0;

    short int code_err = read_array(&arr, &n, &arr_end);
    if (code_err)
    {
        free(arr);
        puts("Invalid input.");
        return code_err;
    }
    
    num1_calc(&num1, arr, arr_end);
    arr_end = del_from_arr(arr, arr_end, num1, &n);
    
    arr = memory_changer(&arr, n, &code_err, &arr_end);
    if (code_err)
    {
        free(arr);
        fprintf(stderr, "Memory allocation error, try again.\n");
        return code_err;
    }
    
    num2_calc(&num2, arr, arr_end);

    code_err = read_number(&p, n);
    if (code_err)
    {
        free(arr);
        fprintf(stderr, "Invalid P number.\n");
        return code_err;
    }
    
    arr = memory_changer(&arr, EXTRA_PLACES + n, &code_err, &arr_end);
    if (code_err)
    {
        free(arr);
        fprintf(stderr, "Memory allocation error, try again.\n");
        return code_err;
    }

    add_to_arr(arr, arr_end - EXTRA_PLACES, arr + p, num2);
    print_result(arr, arr_end);
    free(arr);

    return OK;
}
