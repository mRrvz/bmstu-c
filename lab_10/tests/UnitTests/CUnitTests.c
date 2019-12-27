#include <CUnit/Basic.h>

// ======= HELPER FUNCS =========

int init_suite_success(void) { return 0; }
int clean_suite_success(void) { return 0; }

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

    if ((NULL == CU_add_test(pSuite, "test of ", test_avg_columns_counter)) ||
        (NULL == CU_add_test(pSuite, "test of ", test_max_rows_counter)) ||
        (NULL == CU_add_test(pSuite, "test of ", test_square_matrix)) ||
        (NULL == CU_add_test(pSuite, "test of ", test_matrix_equalization)) ||
        (NULL == CU_add_test(pSuite, "test of ", test_null_degree_checker)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
