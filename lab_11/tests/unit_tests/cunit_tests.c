#include <stdio.h>
#include <CUnit/Basic.h>
#include "../../snprintf.h"

#define MAX_INT 2147483647
#define MAX_LONG 9223372036854775807

int init_suite_success(void)
{
    return 0;
}

int clean_suite_success(void)
{
    return 0;
}

static void double_percent(void)
{
    int size = 50;
    char format[30] = "prc prc %%";

    char buff1[60] = "superteststringstringstringstring string string string test";
    int code1 = my_snprintf(buff1, size, format);

    char buff2[60] = "superteststringstringstringstring string string string test";
    int code2 = snprintf(buff2, size, format);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void null_test(void)
{
    int size = 0;
    char format[30] = "%d test 1234";
    int code1 = my_snprintf(NULL, size, format, 10);
    int code2 = snprintf(NULL, size, format, 10);

    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
}


static void without_specifier(void)
{
    int size = 30;
    char format[30] = "format without specifier";

    char buff1[20] = "test buffer";
    int code1 = my_snprintf(buff1, size, format);

    char buff2[20] = "test buffer";
    int code2 = snprintf(buff2, size, format);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void size_smaller_than_format(void)
{
    int size = 12;
    long number = 10000;
    char format[30] = "specifier test: %ld";

    char buff1[20] = "test_buffer";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[20] = "test_buffer";
    int code2 = snprintf(buff2, size, format, number);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void null_format(void)
{
    int size = 30;
    char format[30] = "\0";

    char buff1[20] = "testbuff";
    int code1 = my_snprintf(buff1, size, format);

    char buff2[20] = "testbuff";
    int code2 = snprintf(buff2, size, format);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void null_buffer(void)
{
    int size = 30;
    int number = 999;
    char format[30] = "test format %d";

    char buff1[20] = "\0";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[20] = "\0";
    int code2 = snprintf(buff2, size, format, number);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void invalid_specifier()
{
    int size = 30;
    char format[30] = "invalid %r %l,";

    char buff1[40] = "buffer buffer buffer buffer";
    int code1 = my_snprintf(buff1, size, format);

    char buff2[40] = "buffer buffer buffer buffer";
    int code2 = snprintf(buff2, size, format);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void null_size()
{
    int size = 0;
    char format[30] = "test format string";

    char buff1[40] = "buffer buffer buffer buffer";
    int code1 = my_snprintf(buff1, size, format);

    char buff2[40] = "buffer buffer buffer buffer";
    int code2 = snprintf(buff2, size, format);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void overflow_size()
{
    int size = 999;
    char format[30] = "negative size";

    char buff1[40] = "buffer buffer buffer buffer";
    int code1 = my_snprintf(buff1, size, format);

    char buff2[40] = "buffer buffer buffer buffer";
    int code2 = snprintf(buff2, size, format);
    //printf("%d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void test_not_specifier(void)
{
    null_buffer();
    null_format();
    without_specifier();
    size_smaller_than_format();
    invalid_specifier();
    null_size();
    overflow_size();
    double_percent();
    null_test();
}

static void d_three_arguments(void)
{
    int size = 49;
    int number1 = 121, number2 = 8, number3 = MAX_INT;
    char format[100] = "three args: %d  ARG1 %d arg2 %d arg_three";

    char buff1[100] = "test_string";
    int code1 = my_snprintf(buff1, size, format, number1, number2, number3);

    char buff2[100] = "test_string";
    int code2 = snprintf(buff2, size, format, number1, number2, number3);
    CU_ASSERT(code1 == code2);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void d_one_argument(void)
{
    int size = 30;
    int number = 3900;
    char format[19] = "test 123 %d string";

    char buff1[30] = "superstring";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[30] = "superstring";
    int code2 = snprintf(buff2, size, format, number);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void d_negative_argument(void)
{
    int size = 30;
    int number = -999;
    char format[19] = "test %d string";

    char buff1[30] = "superstring";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[30] = "superstring";
    int code2 = snprintf(buff2, size, format, number);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void test_d_specifier(void)
{
    d_one_argument();
    d_three_arguments();
    d_negative_argument();
}

static void i_negative_argument(void)
{
    int size = 40;
    int number1 = -0xE2;
    char format[30] = "negative 0x: %i";

    char buff1[60] = "test test test test test test test test";
    int code1 = my_snprintf(buff1, size, format, number1);

    char buff2[60] = "test test test test test test test test";
    int code2 = snprintf(buff2, size, format, number1);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void i_three_different_agruments(void)
{
    int size = 40;
    int number1 = 975, number2 = -017777777777;
    unsigned number3 = 0x7FFFFFFF;
    char format[30] = "%i three %i spec: %i";

    char buff1[60] = "test test test test test test test test";
    int code1 = my_snprintf(buff1, size, format, number1, number2, number3);

    char buff2[60] = "test test test test test test test test";
    int code2 = snprintf(buff2, size, format, number1, number2, number3);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void i_one_argument(void)
{
    int size = 30;
    int number = 404;
    char format[30] = "i specifier test %i";

    char buff1[30] = "superteststring";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[30] = "superteststring";
    int code2 = snprintf(buff2, size, format, number);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void test_i_specifier(void)
{
    i_one_argument();
    i_three_different_agruments();
    i_negative_argument();
}

static void o_three_arguments(void)
{
    int size = 55;
    unsigned number1 = 053, number2 = 07, number3 = 04111;
    char format[100] = "three %o ar %o s %o";

    char buff1[100] = "test string";
    int code1 = my_snprintf(buff1, size, format, number1, number2, number3);

    char buff2[100] = "test string";
    int code2 = snprintf(buff2, size, format, number1, number2, number3);
    CU_ASSERT(code1 == code2);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void o_one_argument(void)
{
    int size = 30;
    int number = 0777;
    char format[30] = "One %o argument...";

    char buff1[60] = "superteststringstringstringstring string";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[60] = "superteststringstringstringstring string";
    int code2 = snprintf(buff2, size, format, number);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void test_o_specifier(void)
{
    o_one_argument();
    o_three_arguments();
}

static void ld_three_arguments(void)
{
    int size = 80;
    long number1 = (long)MAX_INT + 9999, number2 = (long)MAX_INT + 3000, number3 = (long)MAX_INT * 2;
    char format[100] = "three long args: %ld %ld %ld";

    char buff1[100] = "test_string";
    int code1 = my_snprintf(buff1, size, format, number1, number2, number3);

    char buff2[100] = "test_string";
    int code2 = snprintf(buff2, size, format, number1, number2, number3);
    CU_ASSERT(code1 == code2);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void ld_negative_argument(void)
{
    int size = 60;
    long number = -MAX_LONG;
    char format[19] = "negative %ld string";

    char buff1[60] = "superstring";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[60] = "superstring";
    int code2 = snprintf(buff2, size, format, number);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void ld_one_argument(void)
{
    int size = 50;
    long number = MAX_LONG;
    char format[19] = "max %ld ld";

    char buff1[50] = "superstring";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[50] = "superstring";
    int code2 = snprintf(buff2, size, format, number);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void test_ld_specifier(void)
{
    ld_one_argument();
    ld_three_arguments();
    ld_negative_argument();
}

static void li_three_differnt_arguments(void)
{
    int size = 80;
    long number1 = (long)MAX_INT + 9999, number2 = 025753603777, number3 = 0xEB49D1FF;
    char format[100] = "three long integers: %li %li %li";

    char buff1[100] = "testing string str str ssssssssssssssssssssssssssssssss";
    int code1 = my_snprintf(buff1, size, format, number1, number2, number3);

    char buff2[100] = "testing string str str sssssssssssssssssssssssssssssss";
    int code2 = snprintf(buff2, size, format, number1, number2, number3);
    CU_ASSERT(code1 == code2);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void li_negative_argument(void)
{
    int size = 60;
    long number = -0x7FFFFFFFFFFFFFFF;
    char format[25] = "min negative %li string";

    char buff1[60] = "superstringtest";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[60] = "superstringtest";
    int code2 = snprintf(buff2, size, format, number);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void li_one_argument(void)
{
    int size = 50;
    long number = 0777777777777777777777;
    char format[19] = "max %li li";

    char buff1[50] = "superstring";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[50] = "superstring";
    int code2 = snprintf(buff2, size, format, number);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void lo_three_arguments(void)
{
    int size = 55;
    long unsigned number1 = 0647, number2 = 0, number3 = 05432222403643;
    char format[100] = "long %lo %lo %lo unsigned";

    char buff1[100] = "test string";
    int code1 = my_snprintf(buff1, size, format, number1, number2, number3);

    char buff2[100] = "test string";
    int code2 = snprintf(buff2, size, format, number1, number2, number3);
    CU_ASSERT(code1 == code2);
    //printf("AAA: %d %d -- CODES\n%s \n %s\n\n", code1, code2, buff1, buff2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void lo_one_argument(void)
{
    int size = 50;
    long unsigned number = 05575065403647;
    char format[30] = "One long %lo";

    char buff1[60] = "superteststringstringstringstring string string string test";
    int code1 = my_snprintf(buff1, size, format, number);

    char buff2[60] = "superteststringstringstringstring string string string test";
    int code2 = snprintf(buff2, size, format, number);
    CU_ASSERT(code1 == code2);
    CU_ASSERT(!strcmp(buff1, buff2));
}

static void test_li_specifier(void)
{
    li_one_argument();
    li_three_differnt_arguments();
    li_negative_argument();
}

static void test_lo_specifier(void)
{
    lo_one_argument();
    lo_three_arguments();
}

int main(void)
{
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    pSuite = CU_add_suite("my_snprintf tests", init_suite_success, clean_suite_success);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of %d specifier", test_d_specifier)) ||
        (NULL == CU_add_test(pSuite, "test of %i specifier", test_i_specifier)) ||
        (NULL == CU_add_test(pSuite, "test of %o specifier", test_o_specifier)) ||
        (NULL == CU_add_test(pSuite, "test of %ld specifier", test_ld_specifier)) ||
        (NULL == CU_add_test(pSuite, "test of %li specifier", test_li_specifier)) ||
        (NULL == CU_add_test(pSuite, "test of %lo specifier", test_lo_specifier)) ||
        (NULL == CU_add_test(pSuite, "not specifier tests", test_not_specifier)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
