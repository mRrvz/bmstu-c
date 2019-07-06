#include <stdio.h>

#define OK 0
#define APPROPRIATE 0
#define INAPPROPRIATE 1
#define COUNT_CORRECTNESS_VARIABLES 1
#define SIZE_ERROR_INPUT 1
#define ELEMENTS_ERROR_INPUT 2
#define ARRAY_IS_EMPTY 3

#define MAX_ARRAY_SIZE 10
#define MIN_ARRAY_SIZE 1
#define MAX_ARRAY_COPY_SIZE MAX_ARRAY_SIZE

#define ELEMENT_EXIST 0
#define NON_EXIST_ELEMENT 1

const int equal_first_and_last_digit(int number)
{   
    const int last_digit = number % 10;
    int first_digit = 0;
    
    while (number != 0)
    {   
        first_digit = number;
        number = number / 10;
    }

    if (last_digit == first_digit)
    {
        return APPROPRIATE;
    }
    else
    {
        return INAPPROPRIATE;
    }
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
        return ELEMENTS_ERROR_INPUT;
    }

    return OK;
}

const int copy_elements_in_new_array(const int *const array, int *const array_copy, 
    const int array_size, int *const pointer_size)
{
    int array_copy_size = 0;

    for (int i = 0; i < array_size; i++)
    {
        if (equal_first_and_last_digit(array[i]) == APPROPRIATE)
        {
            if (array_copy_size >= MAX_ARRAY_COPY_SIZE)
            {
                return NON_EXIST_ELEMENT;
            }
            array_copy[array_copy_size] = array[i];
            array_copy_size++;
        }
    }
    
    *pointer_size = array_copy_size;
    return ELEMENT_EXIST;
}

void print_array(const int *const array, const int array_copy_size)
{
    puts("Copied array: ");

    for (int i = 0; i < array_copy_size; i++)
    {
        printf("%d ", array[i]);
    }
}

int main()
{
    setbuf(stdout, NULL);

    int array[MAX_ARRAY_SIZE] = { 0 };
    int array_copy[MAX_ARRAY_COPY_SIZE] = { 0 };
    int array_size;
    int check_copy_size = ELEMENT_EXIST;
    int array_copy_size = 0;
    int *const pointer_size = &array_copy_size;

    puts("Enter size of array: ");
    const int check_input = scanf("%d", &array_size);
    if (check_input != COUNT_CORRECTNESS_VARIABLES || array_size > MAX_ARRAY_SIZE || array_size < MIN_ARRAY_SIZE)
    {
        return SIZE_ERROR_INPUT;
    }

    const int correctness_entered_elements = enter_array(array, array_size);
    if (correctness_entered_elements != OK)
    {
        return correctness_entered_elements;
    }
    
    check_copy_size = copy_elements_in_new_array(array, array_copy, array_size, pointer_size);
    if (check_copy_size == NON_EXIST_ELEMENT)
    {
        return check_copy_size;
    }

    if (0 == array_copy_size)
    {
        return ARRAY_IS_EMPTY;
    }
    
    print_array(array_copy, array_copy_size);

    return OK;
}

