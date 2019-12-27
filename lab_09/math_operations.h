#ifndef __MATH_OPERATIONS_H__
#define __MATH_OPERATIONS_H__

#include <stdint.h>
#include "matrix_struct.h"

int64_t avg_columns_counter(matrix_t *const matrix, const unsigned column_numb);

int64_t max_rows_counter(matrix_t *const matrix, const unsigned row_numb);

int matrix_multiplication(const matrix_t matrix_a, const matrix_t matrix_b, matrix_t *const matrix_result);

#endif
