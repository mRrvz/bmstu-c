#include <stdio.h>
 
#define OK 0
#define ERROR_INPUT_SIZE 1
#define ERROR_INPUT_ELEMENTS 2
#define NO_NEGATIVE_ELEMENTS 3
#define COUNT_CORRECTNESS_ELEMENTS 1
#define MAX_ARRAY_SIZE 10
#define MIN_ARRAY_SIZE 1
 
const int enter_array(int *const array, const int size_array, 
    int *const count_negative, double *const sum_negative)
{  
    int check_size_array = 0;

    puts("Enter array: ");
 
    for (int i = 0; i < size_array; i++)
    {
        check_size_array += scanf("%d", &array[i]);
 
        if (array[i] < 0)
        {
            *count_negative += 1;
            *sum_negative += array[i];
        }
    }
    
    if (check_size_array != size_array)
    {
        return ERROR_INPUT_ELEMENTS;
    }
   
    return OK;
}

int main()
{
    setbuf(stdout, NULL);
 
    int size_array;
    int count_negative = 0;
    int *const pointer_count_negative = &count_negative;
    double sum_negative_elements = 0;
    double *const pointer_sum_negative = &sum_negative_elements;
    int array[MAX_ARRAY_SIZE] = { 0 };

    puts("Enter size of array: ");
   
    const int check_input_size = scanf("%d", &size_array);
 
    if (check_input_size != COUNT_CORRECTNESS_ELEMENTS || size_array > MAX_ARRAY_SIZE || size_array < MIN_ARRAY_SIZE)
    {
        return ERROR_INPUT_SIZE;
    }
 
    const int correctness_entered_elements = enter_array(array, 
        size_array, pointer_count_negative, pointer_sum_negative);
    
    if (correctness_entered_elements != OK)
    {
        return correctness_entered_elements;
    }

    if (0 == count_negative)
    {
        return NO_NEGATIVE_ELEMENTS;
    }

    const double average_negative_sum = sum_negative_elements / count_negative;
    
    printf("Average of negative elements is: %lf", average_negative_sum);

    return OK;
}

