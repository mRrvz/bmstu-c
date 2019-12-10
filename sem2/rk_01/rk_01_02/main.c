#include <stdio.h>

#define OK 0
#define INPUT_ERR 1
#define IS_FIBB 0
#define NOT_FIBB 1
#define IS_SIMPLE 0
#define NOT_SIMPLE 1

int is_fibb(int number)
{
    int fib1 = 1, fib2 = 1;

    while (fib1 < number || fib2 < number)
    {
        int fib_sum = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib_sum;
    }
    
    if (number == fib1 || number == fib2)
    {
        return IS_FIBB;
    }

    return NOT_FIBB;
}

int is_simple(int number)
{
    int count = 0;
    
    for (int i = 1; i < number; i++)
    {
        if (number % i == 0)
        {
            count++;
        }
    }

    if (count == 1)
    {
        return IS_SIMPLE;
    }

    return NOT_SIMPLE;
}

void check_number(int number)
{
    for (int i = 0; i < number; i++)
    {
        if (is_fibb(i) == IS_FIBB && is_simple(i) == IS_SIMPLE)
        {
            printf("%d ", i);
        }
    }
}

int main()
{
    int number;

    if (scanf("%d", &number) != 1 || number < 1)
    {
        return INPUT_ERR;
    }
    
    check_number(number);

    return OK;
}
