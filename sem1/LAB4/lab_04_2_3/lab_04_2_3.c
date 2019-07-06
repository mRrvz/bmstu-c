#include <stdio.h>
#include <math.h>

#define OK 0
#define ERROR_INPUT_SIZE 1
#define ERROR_INPUT_ELEMENTS 2
#define ERROR_EMPTY_ARRAY 3
#define COUNT_CORRECTNESS_ELEMENTS 1

#define MAX_ARRAY_SIZE 10
#define MIN_ARRAY_SIZE 1

const int is_full_square(int *const array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {   
        double full_square_double = sqrt(array[i]);
        int full_square_int = full_square_double;

        if (full_square_int == full_square_double)
        {
            for (int k = i; k < array_size; k++)
            {
                array[k] = array[k + 1];
            }
            array_size--;
            i--;
        }
    }

    return array_size;
}

const int enter_array(int *const array, const int array_size)
{
    int check_size_array = 0;
    puts("Enter array: ");

    for (int i = 0; i < array_size; i++)
    {
        check_size_array += scanf("%d", &array[i]);
    }

    if (check_size_array != array_size)
    {
        return ERROR_INPUT_ELEMENTS;
    }

    return OK;
}

void print_array(const int *const array, const int size_array)
{
    puts("Updated array: ");
    for (int i = 0; i < size_array; i++)
    {
        printf("%d ", array[i]);
    }
}

int main()
{
    setbuf(stdout, NULL);
    int array[MAX_ARRAY_SIZE] = { 0 };
    int array_size;

    puts("Enter size of array: ");
    const int check_input_size = scanf("%d", &array_size);
    if (check_input_size != COUNT_CORRECTNESS_ELEMENTS || array_size > MAX_ARRAY_SIZE || array_size < MIN_ARRAY_SIZE)
    {
        return ERROR_INPUT_SIZE;
    }

    const int correctness_entered_elements = enter_array(array, array_size);
    if (correctness_entered_elements != OK)
    {
        return correctness_entered_elements;
    }

    const int new_array_size = is_full_square(array, array_size);
    if (0 == new_array_size)
    {
        return ERROR_EMPTY_ARRAY;
    }

    print_array(array, new_array_size);

    return OK;
}

