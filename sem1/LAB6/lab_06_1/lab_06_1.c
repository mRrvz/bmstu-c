#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define N 10
#define MAX_LEN_STR 15
#define COUNT_TESTS 3
#define TEST_OK 1
#define TEST_NOT_OK 0
#define OK 0

char *my_strrchr(char *const str, const int symb_code)
{
    int i = 0;
    char *pointer = NULL;

    while (str[i])
    {
        if (str[i] == (char)symb_code)
        {
            pointer = &str[i];
        }
        i++;
    }

    if (symb_code == '\0')
    {
        pointer = &str[i];
    }

    return pointer;
}

char *my_strchr(const char *const string, const int symb_code)
{
    int i = 0;
    if (symb_code < 0 || symb_code > 255)
    {
        return NULL;
    }

    while (string[i])
    {
        if (string[i] == (char)symb_code)
        {
            return (char *)&string[i];
        }
        ++i;
    }
    
    if (symb_code == 0)
    {
        return (char*)&string[i];
    }

    return NULL;
}

size_t my_strcspn(const char *const str1, const char *const str2)
{
    int i = 0;
    while (str1[i])
    {
        int j = 0;
        while (str2[j])
        {
            if (str2[j] == str1[i])
            {
                return i;
            }
            ++j;
        }
        ++i;
    }

    return i;
}


size_t my_strspn(const char *const str1, const char *const str2)
{
    int i = 0;
    if (str2[i] == '\0')
    {
        return i;
    }

    while (str1[i])
    {
        int j = 0;
        while (str2[j] && str2[j] != str1[i])
        {
            ++j;
        }
        if (str2[j] != str1[i])
        {
            return i;
        }
        ++i;
    }

    return i;
}

char *my_strpbrk(const char *const str1, const char *const str2)
{
    int i = 0;
    if (str2[i] == '\0')
    {
        return NULL;
    }

    while (str1[i])
    {
        int j = 0;
        while (str2[j])
        {
            if (str1[i] == str2[j])
            {
                return (char *)&str1[i];
            }
            ++j;
        }
        ++i;
    }

    return NULL;
}

const int strrchr_tests(char *const array, const int code)
{
    if (my_strrchr(array, code) == strrchr(array, code))
    {
        return TEST_OK;
    }

    return TEST_NOT_OK;
}

const int strchr_tests(const char *const array, const int code)
{
    if (my_strchr(array, code) == strchr(array, code))
    {
        return TEST_OK;
    }

    return TEST_NOT_OK;
}

const int strcspn_tests(const char *const array, const char *const delim)
{
    if (my_strcspn(array, delim) == strcspn(array, delim))
    {
        return TEST_OK;
    }

    return TEST_NOT_OK;
}

const int strspn_tests(const char *const array, const char *const delim)
{
    if (my_strspn(array, delim) == strspn(array, delim))
    {
        return TEST_OK;
    }

    return TEST_NOT_OK;
}

const int strpbrk_tests(const char *const array, const char *const delim)
{
    if (my_strpbrk(array, delim) == strpbrk(array, delim))
    {
        return TEST_OK;
    }

    return TEST_NOT_OK;
}

void print_res(const int num, const int res)
{
    printf("Test %d: %d\n", num, res);
}

int main(void)
{
    char tests_arr[COUNT_TESTS][MAX_LEN_STR] = { "this is a test", "TestData", "" };
    char delims[COUNT_TESTS][COUNT_TESTS] = { "sr", "kj", "qw" };
    char symbols_code[COUNT_TESTS] = { 116, 0, 36 };

    puts("Strpbrk tests: ");
    for (int i = 0; i < COUNT_TESTS; i++)
    {
        print_res(i + 1, strpbrk_tests(tests_arr[i], delims[i]));
    }                
    
    puts("Strspn tests: ");
    for (int i = 0; i < COUNT_TESTS; i++)
    {
        print_res(i + 1, strspn_tests(tests_arr[i], delims[i]));
    }

    puts("Strcspn tests: ");
    for (int i = 0; i < COUNT_TESTS; i++)
    {
        print_res(i + 1, strcspn_tests(tests_arr[i], delims[i]));
    }

    puts("Strchr tests: ");
    for (int i = 0; i < COUNT_TESTS; i++)
    {
        print_res(i + 1, strchr_tests(tests_arr[i], symbols_code[i]));
    }

    puts("Strrchr tests: ");
    for (int i = 0; i < COUNT_TESTS; i++)
    {
        print_res(i + 1, strrchr_tests(tests_arr[i], symbols_code[i]));
    }

    return OK;
}
