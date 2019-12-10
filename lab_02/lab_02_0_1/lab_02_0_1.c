#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define INPUT_ERROR 1
#define CORRECT_COUNT_OF_VARIABLES 2

float pow_func(int n, int a)
{
    float answer = 1;
    int count_pow = 0;

    while (abs(n) > count_pow)
    {
        answer *= a;
        count_pow++;
    }

    if (n < 0 && a != 0)
    {
        answer = 1 / answer;
    }

    return answer;
}


int main()
{
    setbuf(stdout, NULL);

    int a; 
    int n = 0;
    int check_count = 0;
    
    puts("Enter A and N: ");
    check_count = scanf("%d %d", &a, &n);

    if (n <= 0 || check_count < CORRECT_COUNT_OF_VARIABLES) 
    {
        return INPUT_ERROR;
    }

    printf("Answer: %.5f", pow_func(n, a));

    return OK;
}

