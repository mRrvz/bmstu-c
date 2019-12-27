#ifndef __MATRIX_OPERATIONS_H__
#define __MATRIX_OPERATIONS_H__

#include "matrix_struct.h"

int new_matrix(matrix_t *const matrix);

void free_memory(matrix_t *const matrix);

int memory_changer(matrix_t *const matrix, const int square_size);

void square_matrix(matrix_t *const matrix);

void matrix_equalization(matrix_t *const matrix, unsigned diff);

void null_degree_checker(matrix_t *const matrix_a, matrix_t *const matrix_b);

int create_new_matrix(const matrix_t matrix_a, matrix_t *const matrix_result);

#endif
