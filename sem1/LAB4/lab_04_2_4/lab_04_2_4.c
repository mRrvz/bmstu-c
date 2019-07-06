#include <stdio.h>

#define OK 0
#define ERROR_INPUT_SIZE 1
#define ERROR_INPUT_ELEMENTS 2
#define COUNT_CORRECTNESS_VARIABLES 1

#define MAX_ARRAY_SIZE 10
#define MIN_ARRAY_SIZE 1

void choice_sort(int *const array, const int array_size)
{
    for (int i = 0; i < array_size - 1; i++)
    {
        int index_min_element = i;

        for (int j = i + 1; j < array_size; j++)
        {
            if (array[j] < array[index_min_element])
            {
                index_min_element = j;
            }
        }

        const int template = array[i];
        array[i] = array[index_min_element];
        array[index_min_element] = template;
    }
}

const int enter_array(int *const array, const int array_size)
{
    int check_array_size = 0;
    puts("Enter array: ");
    for (int i = 0; i < array_size; i++)
    {
        check_array_size += scanf("%d", &array[i]);
    }

    if (check_array_size != array_size)
    {
        return ERROR_INPUT_ELEMENTS;
    }
 
    return OK;
}

void print_array(const int *const array, const int array_size)
{
    puts("Sorted array: ");
    for (int i = 0; i < array_size; i++)
    {
        printf("%d ", array[i]);
    }
}

int main()
{
    setbuf(stdout, NULL);
    int array[MAX_ARRAY_SIZE] = { 0 };
    int array_size = 0;

    puts("Enter size of array: ");
    const int check_input = scanf("%d", &array_size);
    if (check_input != COUNT_CORRECTNESS_VARIABLES || array_size > MAX_ARRAY_SIZE || array_size < MIN_ARRAY_SIZE)
    {
        return ERROR_INPUT_SIZE;
    }

    const int correctness_entered_elements = enter_array(array, array_size);
    if (correctness_entered_elements != OK)
    {
        return correctness_entered_elements;
    }
    
    choice_sort(array, array_size);
    print_array(array, array_size);

    return OK;
}
