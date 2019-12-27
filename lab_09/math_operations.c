#include <stdint.h>
#include <math.h>

#include "matrix_struct.h"
#include "matrix_operations.h"
#include "math_operations.h"

#define OK 0
#define MEMORY_ERROR 3

// Подсчёт среднего арифметического для заданного столбца
int64_t avg_columns_counter(matrix_t *const matrix, const unsigned column_numb)
{
    int64_t sum = 0;

    for (unsigned i = 0; i < matrix->row; i++)
    {
        sum += matrix->matrix[i][column_numb];
    }

    double float_sum = floor((double)sum / matrix->row);

    return float_sum;
}

// Функция находит максимальный элемент в заданной строке
int64_t max_rows_counter(matrix_t *const matrix, const unsigned row_numb)
{
    int64_t max = matrix->matrix[row_numb][0];

    for (unsigned i = 0; i < matrix->column; i++)
    {
        if (matrix->matrix[row_numb][i] > max)
        {
            max = matrix->matrix[row_numb][i];
        }
    }

    return max;
}

static void multiplication_two_matrix(const matrix_t matrix_a, const matrix_t matrix_b, matrix_t *const matrix_result)
{
    for (unsigned i = 0; i < matrix_a.row; i++)
    {
        for (unsigned j = 0; j < matrix_a.column; j++)
        {
            matrix_result->matrix[i][j] = 0;

            for (unsigned k = 0; k < matrix_b.column; k++)
            {
                matrix_result->matrix[i][j] += matrix_a.matrix[i][k] * matrix_b.matrix[k][j];
            }
        }
    }
}

static void copy_matrix(matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    for (unsigned i = 0; i < matrix_a->row; i++)
    {
        for (unsigned j = 0; j < matrix_a->column; j++)
        {
            matrix_a->matrix[i][j] = matrix_b->matrix[i][j];
        }
    }
}

// Возведение матрицы в степень
static int matrix_degree_exponentiation(matrix_t matrix, matrix_t *const matrix_result)
{
    matrix_t temp_matrix;

    if (create_new_matrix(matrix, &temp_matrix))
    {
        return MEMORY_ERROR;
    }

    if (create_new_matrix(matrix, matrix_result))
    {
        return MEMORY_ERROR;
    }

    copy_matrix(&temp_matrix, &matrix);

    for (unsigned i = 0; i < matrix.degree - 1; i++)
    {
        multiplication_two_matrix(matrix, temp_matrix, matrix_result);
        copy_matrix(&temp_matrix, matrix_result);
    }

    copy_matrix(matrix_result, &temp_matrix);
    free_memory(&temp_matrix);

    return OK;
}

// Функция перемножает две матрицы, возводя их в заданную степень
int matrix_multiplication(const matrix_t matrix_a, const matrix_t matrix_b, matrix_t *const matrix_result)
{
    matrix_t matrix_a_degree, matrix_b_degree;

    if (matrix_degree_exponentiation(matrix_a, &matrix_a_degree))
    {
        return MEMORY_ERROR;
    }

    if (matrix_degree_exponentiation(matrix_b, &matrix_b_degree))
    {
        return MEMORY_ERROR;
    }

    multiplication_two_matrix(matrix_a_degree, matrix_b_degree, matrix_result);

    free_memory(&matrix_a_degree);
    free_memory(&matrix_b_degree);

    return OK;
}
