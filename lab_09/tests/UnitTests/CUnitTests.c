#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../../matrix_struct.h"
#include "../../matrix_operations.h"
#include "../../math_operations.h"


// ======= HELPER FUNCS =========

int init_suite_success(void)
{ 
    return 0; 
}

int clean_suite_success(void) 
{ 
    return 0; 
}

static int matrix_checker(const matrix_t matrix_a, const matrix_t matrix_b)
{
    for (unsigned i = 0; i < matrix_a.row; i++)
    {    
        for (unsigned j = 0; j < matrix_a.column; j++)
        {
            if (matrix_a.matrix[i][j] != matrix_b.matrix[i][j])
            {
                return 1;
            }
        }
    }

    return 0;
}

static void matrix_init(matrix_t *const matrix)
{
    for (unsigned i = 0; i < matrix->row; i++)
    {    
        for (unsigned j = 0; j < matrix->column; j++)
        { 
            matrix->matrix[i][j] = i;
        }
    }
}

// ========== TESTING SYSTEM ==========

static void avg_column_first_column(void)
{
    matrix_t matrix;
    matrix.row = 3;
    matrix.column = 1;
    new_matrix(&matrix);
    matrix.matrix[0][0] = 1;
    matrix.matrix[1][0] = 2;
    matrix.matrix[2][0] = 5;
    int64_t result = 2;

    CU_ASSERT(result == avg_columns_counter(&matrix, 0));
    free_memory(&matrix);
}

static void avg_column_last_column(void)
{
    matrix_t matrix;
    matrix.row = 4;
    matrix.column = 4;
    new_matrix(&matrix);

    matrix.matrix[0][3] = 1;
    matrix.matrix[1][3] = 2;
    matrix.matrix[2][3] = 15;
    matrix.matrix[3][3] = 5;
    int64_t result = 5;

    CU_ASSERT(result == avg_columns_counter(&matrix, 3));
    free_memory(&matrix);
}

static void avg_column_one_element(void)
{
    matrix_t matrix;
    matrix.row = 1;
    matrix.column = 1;
    new_matrix(&matrix);

    matrix.matrix[0][0] = 777;
    int64_t result = 777;

    CU_ASSERT(result == avg_columns_counter(&matrix, 0));
    free_memory(&matrix);
}

static void test_avg_columns_counter(void)
{
    avg_column_first_column();
    avg_column_last_column();
    avg_column_one_element();
}

static void max_row_above_zero_numbers(void)
{
    matrix_t matrix;
    matrix.row = 1;
    matrix.column = 3;
    new_matrix(&matrix);

    matrix.matrix[0][0] = 404;
    matrix.matrix[0][1] = 133;
    matrix.matrix[0][2] = 999;
    int64_t result = 999;

    CU_ASSERT(result == max_rows_counter(&matrix, 0));
    free_memory(&matrix);
}

static void max_row_less_and_more_zero_numbers(void)
{
    matrix_t matrix;
    matrix.row = 1;
    matrix.column = 4;
    new_matrix(&matrix);

    matrix.matrix[0][0] = -123;
    matrix.matrix[0][1] = 743;
    matrix.matrix[0][2] = -433;
    matrix.matrix[0][3] = -89;
    int64_t result = 743;

    CU_ASSERT(result == max_rows_counter(&matrix, 0));
    free_memory(&matrix);
}

static void max_row_less_than_zero(void)
{
    matrix_t matrix;
    matrix.row = 4;
    matrix.column = 4;
    new_matrix(&matrix);

    matrix.matrix[2][0] = -179;
    matrix.matrix[2][1] = -1337;
    matrix.matrix[2][2] = -999;
    matrix.matrix[2][3] = -1979;
    int64_t result = -179;

    CU_ASSERT(result == max_rows_counter(&matrix, 2));
    free_memory(&matrix);
}

static void test_max_rows_counter(void)
{
    max_row_above_zero_numbers();
    max_row_less_and_more_zero_numbers();
    max_row_less_than_zero();
}

static void square_matrix_delete_2_rows(void)
{
    matrix_t matrix, matrix_test;

    matrix.row = 7;
    matrix.column = 5;
    new_matrix(&matrix);
    matrix_init(&matrix);

    matrix_test.row = 5;
    matrix_test.column = 5;
    new_matrix(&matrix_test);
    matrix_init(&matrix_test);

    square_matrix(&matrix);
    CU_ASSERT(matrix.row == 5);
    CU_ASSERT(matrix.column == 5);
    CU_ASSERT(matrix_checker(matrix, matrix_test) == 0);

    free_memory(&matrix);
    free_memory(&matrix_test);
}

static void square_matrix_delete_1_column(void)
{
    matrix_t matrix, matrix_test;

    matrix.row = 8;
    matrix.column = 9;
    new_matrix(&matrix);
    matrix_init(&matrix);

    matrix_test.row = 8;
    matrix_test.column = 8;
    new_matrix(&matrix_test);
    matrix_init(&matrix_test);

    square_matrix(&matrix);
    CU_ASSERT(matrix.row == 8);
    CU_ASSERT(matrix.column == 8);
    CU_ASSERT(matrix_checker(matrix, matrix_test) == 0);

    free_memory(&matrix);
    free_memory(&matrix_test);
}

static void square_matrix_nothing_delete(void)
{
    matrix_t matrix, matrix_test;
    matrix.row = 5;
    matrix.column = 5;
    new_matrix(&matrix);
    matrix_init(&matrix);

    matrix_test.row = 5;
    matrix_test.column = 5;
    new_matrix(&matrix_test);
    matrix_init(&matrix_test);

    square_matrix(&matrix);
    CU_ASSERT(matrix.row == 5);
    CU_ASSERT(matrix.column == 5);
    CU_ASSERT(matrix_checker(matrix, matrix_test) == 0);

    free_memory(&matrix);
    free_memory(&matrix_test);
}

static void test_square_matrix(void)
{
    square_matrix_delete_2_rows();
    square_matrix_delete_1_column();
    square_matrix_nothing_delete();
}

static void equalization_add_1_column_and_row(void)
{
    matrix_t matrix, matrix_test;
    matrix.row = 10;
    matrix.column = 10;
    new_matrix(&matrix);
    matrix_init(&matrix);
    matrix.row = 9;
    matrix.column = 9;

    matrix_test.row = 10;
    matrix_test.column = 10;
    new_matrix(&matrix_test);
    matrix_init(&matrix_test);

    matrix_equalization(&matrix, 1);
    CU_ASSERT(matrix.row == 10);
    CU_ASSERT(matrix.column == 10);

    free_memory(&matrix);
    free_memory(&matrix_test);
}

static void equalization_add_3_column_and_row(void)
{
    matrix_t matrix, matrix_test;
    matrix.row = 6;
    matrix.column = 6;
    new_matrix(&matrix);
    matrix_init(&matrix);
    matrix.row = 3;
    matrix.column = 3;

    matrix_test.row = 6;
    matrix_test.column = 6;
    new_matrix(&matrix_test);
    matrix_init(&matrix_test);

    matrix_equalization(&matrix, 3);
    CU_ASSERT(matrix.row == 6);
    CU_ASSERT(matrix.column == 6);

    free_memory(&matrix);
    free_memory(&matrix_test);
}

static void eqalization_nothing_add(void)
{
    matrix_t matrix, matrix_test;
    matrix.row = 14;
    matrix.column = 14;
    new_matrix(&matrix);
    matrix_init(&matrix);

    matrix_test.row = 14;
    matrix_test.column = 14;
    new_matrix(&matrix_test);
    matrix_init(&matrix_test);

    matrix_equalization(&matrix, 0);
    CU_ASSERT(matrix.row == 14);
    CU_ASSERT(matrix.column == 14);
    CU_ASSERT(matrix_checker(matrix, matrix_test) == 0);

    free_memory(&matrix);
    free_memory(&matrix_test);
}

static void test_matrix_equalization(void)
{
    equalization_add_1_column_and_row();
    equalization_add_3_column_and_row();
    eqalization_nothing_add();
}

static void null_degree_matrix_2x2(void)
{
    matrix_t matrix_a, matrix_b;
    matrix_a.row = 2;
    matrix_a.column = 2;
    matrix_a.degree = 0;
    new_matrix(&matrix_a);

    matrix_b.row = 2;
    matrix_b.column = 2;
    matrix_b.degree = 0;
    new_matrix(&matrix_b);

    null_degree_checker(&matrix_a, &matrix_b);

    CU_ASSERT(matrix_a.matrix[0][0] == 1);
    CU_ASSERT(matrix_b.matrix[0][0] == 1);
    CU_ASSERT(matrix_a.matrix[1][1] == 1);
    CU_ASSERT(matrix_b.matrix[1][1] == 1);
    free_memory(&matrix_a);
    free_memory(&matrix_b);
}

static void null_degree_matrix_1x1(void)
{
    matrix_t matrix_a, matrix_b;
    matrix_a.row = 1;
    matrix_a.column = 1;
    matrix_a.degree = 0;
    new_matrix(&matrix_a);

    matrix_b.row = 2;
    matrix_b.column = 2;
    matrix_b.degree = 7;
    new_matrix(&matrix_b);

    null_degree_checker(&matrix_a, &matrix_b);

    CU_ASSERT(matrix_a.matrix[0][0] == 1);
    free_memory(&matrix_a);
    free_memory(&matrix_b);
}

static void null_degree_matrix_3x3(void)
{
    matrix_t matrix_a, matrix_b;
    matrix_a.row = 1;
    matrix_a.column = 1;
    matrix_a.degree = 12;
    new_matrix(&matrix_a);

    matrix_b.row = 3;
    matrix_b.column = 3;
    matrix_b.degree = 0;
    new_matrix(&matrix_b);

    null_degree_checker(&matrix_a, &matrix_b);

    CU_ASSERT(matrix_b.matrix[0][0] == 1);
    CU_ASSERT(matrix_b.matrix[1][1] == 1);
    CU_ASSERT(matrix_b.matrix[2][2] == 1);
    free_memory(&matrix_a);
    free_memory(&matrix_b);
}

static void test_null_degree_checker(void)
{
    null_degree_matrix_2x2();
    null_degree_matrix_1x1();
    null_degree_matrix_3x3();
}

int main(void)
{
    CU_pSuite pSuite = NULL;
    
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    pSuite = CU_add_suite("POSITIVE TESTS", init_suite_success, clean_suite_success);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of avg_columns_counters)", test_avg_columns_counter)) ||
        (NULL == CU_add_test(pSuite, "test of max_rows_counter()", test_max_rows_counter)) ||
        (NULL == CU_add_test(pSuite, "test of square_matrix()", test_square_matrix)) ||
        (NULL == CU_add_test(pSuite, "test of matrix_equalization(()", test_matrix_equalization)) ||
        (NULL == CU_add_test(pSuite, "test of null_degree_checker()", test_null_degree_checker)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

