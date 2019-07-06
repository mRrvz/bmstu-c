#include <stdio.h>
#include <math.h>
#define OK 0
#define ERROR_INPUT 1
#define CORRECT_COUNT_OF_VARIABLES 2
#define INCORRECT_EPSILON 3

float sum_of_series(float x, float epsilon)
{
    float series_member = 1;
    float sum_of_series = 1;
    int i = 1;
    
    while (fabs(series_member) > epsilon)
    {   
        series_member = series_member * (x / i);
        sum_of_series += series_member;
        i++;
    }    

    return sum_of_series;
}


int check_input(int check_count, float epsilon) 
{
    if (check_count != CORRECT_COUNT_OF_VARIABLES)
    {
        return ERROR_INPUT;
    }

    if (epsilon <= 0 || epsilon > 1)
    {
        return INCORRECT_EPSILON;
    }

    return OK;
}


int main()
{
    setbuf(stdout, NULL);

    int check_count;
    float x, epsilon;
    float approximate, exact;
    float absolute_error, relative_error;

    puts("Enter X and Epsilon: ");
    check_count = scanf("%f %f", &x, &epsilon);
       
    int check_entered_variables = check_input(check_count, epsilon);

    if (check_entered_variables != OK)
    {
        return check_entered_variables;
    }
    
    approximate = sum_of_series(x, epsilon);
   
    puts("Approximation value of e^x:");
    printf("%f", approximate);
    
    exact = expf(x);
    puts("\nExact value of e^x:");
    printf("%f", exact);
    
    absolute_error = fabs(exact - approximate);
    puts("\nAbsolute error:");
    printf("%f", absolute_error);

    relative_error = fabs(absolute_error / exact);
    puts("\nRelative error:");
    printf("%f", relative_error);

    return OK;
}

