#include <stdio.h>
#include <stdlib.h>
 
#define MIN_MATRIX_SIZE 1
#define MAX_MATRIX_SIZE 10
#define POINTER_ARRAY_SIZE (MAX_MATRIX_SIZE * 2)
 
#define ELEMENT_EXIST 0
#define NON_EXIST_ELEMENT 1
#define OK 0
#define ERROR_SIZE_INPUT 1
#define ROWS_ERROR_INPUT 2
#define COLUMNS_ERROR_INPUT 3
#define ELEMENTS_MATRIX_INPUT_ERROR 4
#define COUNT_CORRECT_ELEMENTS_MATRIX 1
#define COUNT_CORRECT_VARIABLES 2
 
#define ROW_CORRECT 0
#define ROW_INCORRECT 1
 
const int sum_of_digit_is_odd(const int *const pointer_array_row, const int columns)
{
    int count_odd_digit = 0;
    for (int i = 0; i < columns; i++)
    {
        int digit = abs(pointer_array_row[i]);
        int sum_of_numbers = 0;
        while (digit != 0)
        {
            sum_of_numbers += digit % 10;
            digit /= 10;
        }
 
        if (sum_of_numbers % 2 == 1)
        {
            count_odd_digit++;
        }
    }
   
    if (count_odd_digit < 2)
    {
        return ROW_INCORRECT;
    }
   
    return ROW_CORRECT;
}
 
const int add_rows_to_matrix(int **const pointer_array, int rows,
    const int columns, int *const inserted_row, int *const pointer_rows)
{
    for (int i = 0; i < rows; i++)
    {
        if (sum_of_digit_is_odd(pointer_array[i], columns) == ROW_CORRECT)
        {
            if (rows >= POINTER_ARRAY_SIZE)
            {
                return NON_EXIST_ELEMENT;
            }
 
            for (int j = (rows - 1); j >= i ; j--)
            {
                pointer_array[j + 1] = pointer_array[j];
            }
            pointer_array[i] = inserted_row;
            rows++;
            i++;
        }
    }
    *pointer_rows = rows;
    return ELEMENT_EXIST;
}
 
void filling_inserted_row(int *const inserted_row, const int columns)
{
    for (int i = 0; i < columns; i++)
    {
        inserted_row[i] = -1;
    }
}
 
void filling_array_of_pointers(int matrix[][MAX_MATRIX_SIZE],
    int **const array_of_pointers, const int rows)
{
    for (int i = 0; i < rows; i++)
    {
        array_of_pointers[i] = &matrix[i][0];
    }
}
 
const int read_matrix(int matrix[][MAX_MATRIX_SIZE], const int rows, const int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (scanf("%d", &matrix[i][j]) != COUNT_CORRECT_ELEMENTS_MATRIX)
            {
                return ELEMENTS_MATRIX_INPUT_ERROR;
            }
        }
    }
   
    return OK;
}
 
const int check_correctness_matrix_size(const int check_variables, const int rows, const int columns)
{
    if (check_variables != COUNT_CORRECT_VARIABLES)
    {
        return ERROR_SIZE_INPUT;
    }
 
    if (rows < MIN_MATRIX_SIZE || rows > MAX_MATRIX_SIZE)
    {
        return ROWS_ERROR_INPUT;
    }
 
    if (columns < MIN_MATRIX_SIZE || columns > MAX_MATRIX_SIZE)
    {
        return COLUMNS_ERROR_INPUT;
    }
 
    return OK;
}
 
void print_array(int **const pointer_array, const int rows, const int columns)
{
    puts("Formed matrix: ");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", pointer_array[i][j]);
        }
    }
}
 
int main(void)
{
    setbuf(stdout, NULL);
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = { 0 };
    int *pointer_array[POINTER_ARRAY_SIZE] = { NULL };
    int inserted_row[MAX_MATRIX_SIZE] = { 0 };
    int rows, columns;
    int check_array_size = ELEMENT_EXIST;
    int *const pointer_rows = &rows;
 
    puts("Enter count rows and columns of matrix: ");
    const int check_variables = scanf("%d %d", &rows, &columns);
    const int input_size_check = check_correctness_matrix_size(check_variables, rows, columns);
    if (input_size_check != OK)
    {
        return input_size_check;
    }
   
    const int check_elements_array = read_matrix(matrix, rows, columns);
    if (check_elements_array != OK)
    {
        return check_elements_array;
    }
 
    filling_inserted_row(inserted_row, columns);
    filling_array_of_pointers(matrix, pointer_array, rows);
    check_array_size = add_rows_to_matrix(pointer_array, rows, columns, inserted_row, pointer_rows);
    if (check_array_size == NON_EXIST_ELEMENT)
    {
        return check_array_size;
    }
    print_array(pointer_array, rows, columns);
 
    return OK;
}
