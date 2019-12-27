#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "read.h"
#include "matrix_operations.h"
#include "math_operations.h"
#include "print.h"
#include "matrix_struct.h"

#define OK 0

int main(void)
{
    setbuf(stdout, NULL);

    matrix_t matrix_a = { 0 }, matrix_b = { 0 }, matrix_result = { 0 };
    int code_err = read_matrix(&matrix_a, &matrix_b);

    if (code_err)
    {
        fprintf(stderr, "Invalid matrix input.\n");
        return code_err;
    }

    // Приведение матриц к квадратному виду
    square_matrix(&matrix_a);
    square_matrix(&matrix_b);

    // Добавление дополнительной памяти для матрицы меньшего разера
    int64_t diff = matrix_a.row - matrix_b.row;
    code_err = (diff > 0) ? memory_changer(&matrix_b, matrix_a.row) : memory_changer(&matrix_a, matrix_b.row);

    if (code_err)
    {
        free_memory(&matrix_a);
        free_memory(&matrix_b);
        fprintf(stderr, "Memory error, try again.\n");
        return code_err;
    }

    // Приведение меньшей матрицы к размеру большой матрицы
    (diff > 0) ? matrix_equalization(&matrix_b, diff) : matrix_equalization(&matrix_a, abs(diff));
    code_err = read_degrees(&matrix_a, &matrix_b);

    if (code_err)
    {
        free_memory(&matrix_a);
        free_memory(&matrix_b);
        fprintf(stderr, "Invalid degree input.\n");
        return code_err;
    }

    // Проверка нулевой степени для матриц
    null_degree_checker(&matrix_a, &matrix_b);
    // Инициализация матрицы с результатом
    code_err = create_new_matrix(matrix_a, &matrix_result);

    if (code_err)
    {
        free_memory(&matrix_a);
        free_memory(&matrix_b);
        free_memory(&matrix_result);
        fprintf(stderr, "Memory error, try again.\n");
        return code_err;
    }

    matrix_multiplication(matrix_a, matrix_b, &matrix_result);
    print_result(matrix_result);

    free_memory(&matrix_a);
    free_memory(&matrix_b);
    free_memory(&matrix_result);

    return OK;
}
