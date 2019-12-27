#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "math_operations.h"
#include "matrix_operations.h"
#include "matrix_struct.h"

#define OK 0
#define MEMORY_ERROR 3

#define DELETE_ROWS 0
#define DELETE_COLUMNS 1

typedef enum boolean
{
    false = 0,
    true = 1
} bool;

// Создание новой матрицы, расположенной в памяти по строкам
int new_matrix(matrix_t *const matrix)
{
    matrix->matrix = malloc(matrix->row * sizeof(int64_t *));

    if (matrix->matrix == NULL)
    {
        matrix->row = 0;
        return MEMORY_ERROR;
    }

    for (unsigned i = 0; i < matrix->row; i++)
    {
        *(matrix->matrix + i) = malloc(matrix->column * sizeof(int64_t));

        if (*(matrix->matrix + i) == NULL)
        {
            matrix->row = i;
            return MEMORY_ERROR;
        }
    }

    return OK;
}

void free_memory(matrix_t *const matrix)
{
    for (unsigned i = 0; i < matrix->row; i++)
    {
        free(matrix->matrix[i]);
    }

    free(matrix->matrix);
}

// Добавление памяти для дополнительных столбцов
static int columns_memory_changer(matrix_t *const matrix, const int change_size)
{
    for (unsigned i = 0; i < matrix->row; i++)
    {
        int64_t *new_ptr = realloc(matrix->matrix[i], change_size * sizeof(int64_t));

        if (new_ptr == NULL)
        {
            return MEMORY_ERROR;
        }

        matrix->matrix[i] = new_ptr;
        new_ptr = NULL;
    }

    return OK;
}

static int rows_memory_changer(matrix_t *const matrix, const int change_size)
{
    // Изменение двойного указателя на массив указателей, для увеличения кол-ва строк
    int64_t **new_matrix_ptr = realloc(matrix->matrix, change_size * sizeof(int64_t *));

    if (new_matrix_ptr == NULL)
    {
        return MEMORY_ERROR;
    }

    matrix->matrix = new_matrix_ptr;

    // Добавление ячеек памяти для новых строк к матрице
    for (unsigned i = matrix->row; i < change_size; i++)
    {
        int64_t *new_ptr = malloc(change_size * sizeof(int64_t));

        if (new_ptr == NULL)
        {
            return MEMORY_ERROR;
        }

        matrix->matrix[i] = new_ptr;
    }

    return OK;
}

int memory_changer(matrix_t *const matrix, const int square_size)
{
    if (rows_memory_changer(matrix, square_size) || columns_memory_changer(matrix, square_size))
    {
        return MEMORY_ERROR;
    }

    return OK;
}

// Функция, которая определяет, нужно удалять строки или столбцы
static bool comparator(int64_t rows, int64_t columns)
{
    return (rows > columns) ? DELETE_COLUMNS : DELETE_ROWS;
}


static void delete_column_by_position(matrix_t *const matrix, unsigned position)
{
    for (unsigned i = 0; i < matrix->row; i++)
    {
        for (unsigned j = position; j < matrix->column - 1; j++)
        {
            matrix->matrix[i][j] = matrix->matrix[i][j + 1];
        }
    }

    matrix->column--;
}

static void delete_row_by_position(matrix_t *const matrix, unsigned position)
{
    for (unsigned i = position; i < matrix->row - 1; i++)
    {
        for (unsigned j = 0; j < matrix->column; j++)
        {
            matrix->matrix[i][j] = matrix->matrix[i + 1][j];
        }
    }

    matrix->row--;
    // Освобождение памяти (строки) сразу при удалении строки, чтобы не было утечки
    free(matrix->matrix[matrix->row]);
}

// Определение максимума в матрице и удаление строки / столбца по признаку, которая выдает переденная функция
static void maximum_counter(matrix_t *const matrix, unsigned count_delete, bool (*f)(int64_t, int64_t))
{
    bool is_row = (*f)(matrix->row, matrix->column);

    for (unsigned k = 0; k < count_delete; k++)
    {
        int max = matrix->matrix[0][0];
        int position = 0;

        for (unsigned i = 0; i < matrix->row; i++)
        {
            for (unsigned j = 0; j < matrix->column; j++)
            {
                if (matrix->matrix[i][j] > max)
                {
                    max = matrix->matrix[i][j];
                    position = (is_row) ? i : j;
                }
            }
        }

        // флаг is_row определяет, нужно удалять строки или столбцы
        (is_row) ? delete_row_by_position(matrix, position) : delete_column_by_position(matrix, position);
    }
}

// Приведение матрицы к квадатному виду
void square_matrix(matrix_t *const matrix)
{
    if (matrix->column != matrix->row)
    {
        maximum_counter(matrix, abs(matrix->row - matrix->column), comparator);
    }
}

void matrix_equalization(matrix_t *const matrix, unsigned diff)
{
    unsigned current_size = matrix->row;

    // Добавление строк в матрицу
    for (unsigned i = 0; i < diff; i++)
    {
        for (unsigned j = 0;  j < matrix->column; j++)
        {
            matrix->matrix[i + current_size][j] = avg_columns_counter(matrix, j);
        }

        matrix->row++;
    }

    // Добавление столбцов в матрицу
    for (unsigned i = 0; i < diff; i++)
    {
        for (unsigned j = 0; j < matrix->row; j++)
        {
            matrix->matrix[j][current_size + i] = max_rows_counter(matrix, j);
        }

        matrix->column++;
    }
}

// Приведение матрицы к единичной
static void one_dimension_matrix(matrix_t *const matrix)
{
    for (unsigned i = 0; i < matrix->row; i++)
    {
        for (unsigned j = 0; j < matrix->column; j++)
        {
            matrix->matrix[i][j] = (i == j);
        }
    }
}


void null_degree_checker(matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    if (0 == matrix_a->degree)
    {
        one_dimension_matrix(matrix_a);
    }

    if (0 == matrix_b->degree)
    {
        one_dimension_matrix(matrix_b);
    }
}

static void init_matrix(matrix_t *const matrix)
{
    for (unsigned i = 0; i < matrix->row; i++)
    {
        memset(matrix->matrix[i], 0, sizeof(int64_t) * matrix->column);
    }
}

// Создание новой, пустой матрицы, с размерами как у matrix_a
int create_new_matrix(const matrix_t matrix_a, matrix_t *const matrix_result)
{
    matrix_result->row = matrix_a.row;
    matrix_result->column = matrix_a.column;

    if (new_matrix(matrix_result))
    {
        return MEMORY_ERROR;
    }

    init_matrix(matrix_result);

    return OK;
}
