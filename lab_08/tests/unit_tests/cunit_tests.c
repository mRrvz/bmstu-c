#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../../arr_oper.h"
#include "../../math_oper.h"

#define EPS 1e-8

int init_suite_success(void) { return 0; }
int clean_suite_success(void) { return 0; }

/* ===== TESTING SYSTEM ===== */

static void test_num1_calc(void)
{
    // TEST1: ONLY POSITIVE NUMBERS
    double test_buff1[5] = { 23.4, 12.4, 21.2, 31.4, 17.5 };
    double res1 = 0;
    double should_be1 = 21.18;
    
    num1_calc(&res1, test_buff1, test_buff1 + 5);
    CU_ASSERT((abs(res1 - should_be1) < EPS));

    // TEST2: ONLY NEGATIVE NUMBERS
    double test_buff2[6] = { -12.1, -34.1, -13.7, -51.6, -21.2, -55.1 };
    double res2 = 0;
    double should_be2 = -31.3;
    
    num1_calc(&res2, test_buff2, test_buff2 + 6);
    CU_ASSERT(abs(res2 - should_be2) < EPS);

    // TEST3: POSTIVIE && NEGATIVE NUMBERS
    double test_buff3[6] = { 404.12, -123.47, -57.4, 99.12, -34.1, 57.4 };
    double res3 = 0;
    double should_be3 = 57.611667;
    
    num1_calc(&res3, test_buff3, test_buff3 + 6);
    CU_ASSERT(abs(res3 - should_be3) < EPS);

    //TEST4: EMPTY ARRAY
    double test_buff4[0] = { };
    double res4 = 0;
    double should_be4 = 0;
    
    num1_calc(&res4, test_buff4, test_buff4 + 0);
    CU_ASSERT(abs(res4 - should_be4) < EPS);
    
    //TEST5: ONLY 1 ELEM IN ARRAY
    double test_buff5[1] = { 133.17 };
    double res5 = 0;
    double should_be5 = 133.17;
    
    num1_calc(&res5, test_buff5, test_buff5 + 1);
    CU_ASSERT(abs(res5 - should_be5) < EPS);
}

static void test_num2_calc(void)
{
    // TEST1: ONLY POSITIVE NUMBERS
    double test_buff1[5] = { 471.23, 231.15, 501.15, 201.2, 501.2 };
    double res1 = 0;
    double should_be1 = 501.2;
    
    num2_calc(&res1, test_buff1, test_buff1 + 5);
    CU_ASSERT((abs(res1 - should_be1) < EPS));

    // TEST2: ONLY NEGATIVE NUMBERS
    double test_buff2[6] = { -777.3, -13.37, -23.8, -99.3, -23.1, -4812.1 };
    double res2 = 0;
    double should_be2 = -13.37;
    
    num2_calc(&res2, test_buff2, test_buff2 + 6);
    CU_ASSERT(abs(res2 - should_be2) < EPS);

    // TEST3: POSTIVIE && NEGATIVE NUMBERS
    double test_buff3[6] = { 653.21, 963.12, -973.23, -12222.12, -23.1722, 960.1 };
    double res3 = 0;
    double should_be3 = 963.12;
    
    num2_calc(&res3, test_buff3, test_buff3 + 6);
    CU_ASSERT(abs(res3 - should_be3) < EPS);

    //TEST4: EMPTY ARRAY
    double test_buff4[0] = { };
    double res4 = 0;
    double should_be4 = *test_buff4;
    
    num2_calc(&res4, test_buff4, test_buff4 + 0);
    CU_ASSERT(abs(res4 - should_be4) < EPS);
    
    //TEST5: ONLY 1 ELEM IN ARRAY
    double test_buff5[1] = { 8632.213 };
    double res5 = 0;
    double should_be5 = 8632.213;
    
    num2_calc(&res5, test_buff5, test_buff5 + 1);
    CU_ASSERT(abs(res5 - should_be5) < EPS);
}

static void test_add_to_arr(void)
{
    // TEST1: STANDART ARRAY
    double test_buff1[6] = { 507.12, -345.12, 4204.199, -109.1, 8.888, 778 };
    double test_buff_should_be1[6] = { 507.12, -345.12, -109.1, 8.888 };
    short int size1 = 6;
    short int should_be_size1 = 4;
    double numb1 = 777.228;
    double *res1 = del_from_arr(test_buff1, test_buff1 + size1, numb1, &size1);
    
    CU_ASSERT_EQUAL(0, memcmp(test_buff1, test_buff_should_be1, should_be_size1));
    CU_ASSERT(should_be_size1 == size1);
    CU_ASSERT_PTR_EQUAL(res1, test_buff1 + should_be_size1);

    // TEST2: EMPTY ARRAY
    double test_buff2[0] = { };
    double test_buff_should_be2[6] = { };
    short int size2 = 0;
    short int should_be_size2 = 0;
    double numb2 = 451.23;
    double *res2 = del_from_arr(test_buff2, test_buff2 + size2, numb2, &size2);
    
    CU_ASSERT_EQUAL(0, memcmp(test_buff2, test_buff_should_be2, should_be_size2));
    CU_ASSERT(should_be_size2 == size2);
    CU_ASSERT_PTR_EQUAL(res2, test_buff2 + should_be_size2);
    
    // TEST3: ONLY 1 ELEM IN ARRAY
    double test_buff3[1] = { 963.1 };
    double test_buff_should_be3[1] = { 963.1 };
    short int size3 = 1;
    short int should_be_size3 = 1;
    double numb3 = 1024.2048;
    double *res3 = del_from_arr(test_buff3, test_buff3 + size3, numb3, &size3);
    
    CU_ASSERT_EQUAL(0, memcmp(test_buff3, test_buff_should_be3, should_be_size3));
    CU_ASSERT(should_be_size3 == size3);
    CU_ASSERT_PTR_EQUAL(res3, test_buff3 + should_be_size3);
}

    
static void test_del_from_arr(void)
{
    // TEST1: STANDART ARRAY
    double test_buff1[9] = {-765.54, 31.23, 299.12, 966.64, -32.12, 863.12 };
    double test_buff_should_be1[9] = { 27.1541, -765.54, 31.23, 299.12, 966.64, -32.12, 27.1541, 863.12, 27.1541 };
    short int size1 = 6;
    short int should_be_size1 = 9;
    double pos1 = 2;
    double numb1 = 27.1541;
    double *res1 = add_to_arr(test_buff1, test_buff1 + size1, &pos1, numb1);

    CU_ASSERT_EQUAL(0, memcmp(test_buff1, test_buff_should_be1, 0));
    CU_ASSERT_PTR_EQUAL(res1, test_buff1 + should_be_size1);
    
    // TEST2: EMPTY ARRAY
    double test_buff2[3] = { };
    double test_buff_should_be2[3] = { 421.2, 421.2, 421.2 };
    short int size2 = 0;
    short int should_be_size2 = 3;
    double pos2 = 0;
    double numb2 = 421.2;
    double *res2 = add_to_arr(test_buff2, test_buff2 + size2, &pos2, numb2);

    CU_ASSERT_EQUAL(0, memcmp(test_buff2, test_buff_should_be2, 0));
    CU_ASSERT_PTR_EQUAL(res2, test_buff2 + should_be_size2);

    //TEST3: ONLY 1 ELEM IN ARRAY
    double test_buff3[4] = { 515.3 };
    double test_buff_should_be3[4] = { 505.40, 505.40, 515.3, 505.40 };
    short int size3 = 1;
    short int should_be_size3 = 4;
    double pos3 = 0;
    double numb3 = 505.40;
    double *res3 = add_to_arr(test_buff3, test_buff3 + size3, &pos3, numb3);

    CU_ASSERT_EQUAL(0, memcmp(test_buff3, test_buff_should_be3, 0));
    CU_ASSERT_PTR_EQUAL(res3, test_buff3 + should_be_size3);

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

    if ((NULL == CU_add_test(pSuite, "test of num1_calc()", test_num1_calc)) ||
        (NULL == CU_add_test(pSuite, "test of num2_calc()", test_num2_calc)) ||
        (NULL == CU_add_test(pSuite, "test of add_to_arr()", test_add_to_arr)) ||
        (NULL == CU_add_test(pSuite, "test of del_from_arr()", test_del_from_arr)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

