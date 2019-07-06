#include <stdio.h>
#define OK 0
#define IS_SIMPLE 1
#define NOT_SIMPLE 0 
#define ERROR_INPUT 1
#define ARRAY_SIZE 100

int delete_first_digit(const int number)
{
    int i = 1;
    while (number / i > 9)
        i *= 10;
    int new_number = number % i;
    return new_number;
}

int is_simple(int number)
{
    int count_del = 0;
    for (int i = 2; i < number; i++)
        if (number % i == 0)
            count_del++;

    if (count_del == 0)
        return IS_SIMPLE;

    return NOT_SIMPLE;
}

int cut_off_numb(int number, const int N)
{
    while (number > N)
    {
        number /= 10;
    }
    return number;
}

const int third_digit(int *array, int number, int index)
{
    while (number >= 100)
    {
        int check_number = cut_off_numb(number, 1000);
        int new_number = number;

        if (is_simple(check_number) == IS_SIMPLE)
        {
            array[index] = check_number;
            index++;
        }

        number = delete_first_digit(new_number);
    }
    
    return index;
}

const int second_digit(int *array, int number, int index)
{
    while (number >= 10)
    {
        int check_number = cut_off_numb(number, 100);
        int new_number = number;
        while (check_number > 100)
        {
            check_number /= 10;
        }
        if (is_simple(check_number) == IS_SIMPLE)
        {
            array[index] = check_number;
            index++;
        }

        number = delete_first_digit(new_number);
    }

    return index;
}

const int first_digit(int *array, int number)
{
    int i = 0;
    int digit = 0;

    while (number != 0)
    {
        digit = number % 10;
        if (is_simple(digit) == IS_SIMPLE)
        {
            array[i] = digit;
            i++;
        }
        number /= 10;
    }
    
    return i;
}

void my_choice_sort(int *const array, const int index)
{
    for (int i = 0; i < index - 1; i++)
    {
        int index_min_element = i;

        for (int j = i + 1; j < index; j++)
        {
            if (array[j] < array[index_min_element])
            {
                index_min_element = j;
            }
        }

        const int temp = array[i];
        array[i] = array[index_min_element];
        array[index_min_element] = temp;
    }
}

void print_array(const int *const array, const int index)
{
    puts("Formed array: ");
    for (int i = 0; i < index; i++)
    {
        printf("%d ", array[i]);
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    int number;
    int array[ARRAY_SIZE] = { 0 };
    puts("Enter number:");
    if (scanf("%d", &number) != 1)
    {
        return ERROR_INPUT;
    }
    
    int index = first_digit(array, number);
    index = second_digit(array, number, index);
    index = third_digit(array, number, index);
    my_choice_sort(array, index);
    print_array(array, index);

    return OK;
}

