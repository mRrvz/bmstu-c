#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdint.h>
//#include <inttypes.h>

#include "read.h"
#include "matrix_struct.h"
#include "matrix_operations.h"

#define OK 0
#define INVALID_SIZES 1
#define NEGATIVE_SIZES 2
#define MEMORY_ERROR 3
#define INVALID_CELL 4
#define INVALID_DEGREES 5
#define NEGATIVE_DEGREES 6

#define READ_ELEMENTS_OK 1

static int enter_matrix(matrix_t *const matrix)
{
    puts("Input number of rows and number of columns: ");
    if (scanf("%"SCNd64, &matrix->row) != READ_ELEMENTS_OK)
    {
        return INVALID_SIZES;
    }

    if (scanf("%"SCNd64, &matrix->column) != READ_ELEMENTS_OK)
    {
        return INVALID_SIZES;
    }

    if (matrix->row <= 0 || matrix->column <= 0)
    {
        return NEGATIVE_SIZES;
    }

    if (new_matrix(matrix))
    {
        return MEMORY_ERROR;
    }

    puts("Input elements of matrix: ");
    for (unsigned i = 0; i < matrix->row; i++)
    {
        for (unsigned j = 0; j < matrix->column; j++)
        {
            if (scanf("%"SCNd64, *(matrix->matrix + i) + j) != READ_ELEMENTS_OK)
            {
                return INVALID_CELL;
            }
        }
    }

    return OK;
}

int read_matrix(matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    int code_error = enter_matrix(matrix_a);
    if (code_error)
    {
        if (code_error != NEGATIVE_SIZES && code_error != INVALID_SIZES)
        {
            free_memory(matrix_a);
        }

        return code_error;
    }

    code_error = enter_matrix(matrix_b);
    if (code_error)
    {
        if (code_error != NEGATIVE_SIZES && code_error != INVALID_SIZES)
        {
            free_memory(matrix_b);
        }

        free_memory(matrix_a);

        return code_error;
    }

    return OK;
}

int read_degrees(matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    puts("Enter number of degrees for matrix A and matrix B: ");
    if (scanf("%"SCNd64, &matrix_a->degree) != READ_ELEMENTS_OK)
    {
        return INVALID_DEGREES;
    }
    if (scanf("%"SCNd64, &matrix_b->degree) != READ_ELEMENTS_OK)
    {
        return INVALID_DEGREES;
    }

    if (matrix_a->degree < 0 || matrix_b->degree < 0)
    {
        return NEGATIVE_DEGREES;
    }

    return OK;
}
