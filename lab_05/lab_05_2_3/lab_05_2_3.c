#include <stdio.h>

#define MIN_MATRIX_SIZE 1
#define MAX_MATRIX_SIZE 10

#define OK 0
#define ERROR_SIZE_INPUT 1
#define ROWS_ERROR_INPUT 2
#define COLUMNS_ERROR_INPUT 3
#define ELEMENTS_MATRIX_INPUT_ERROR 4
#define COUNT_CORRECT_ELEMENTS_MATRIX 1
#define COUNT_CORRECT_VARIABLES 2

void sort_pointers(int **const pointer_array, const int index_row)
{
    int *const temp_pointer = pointer_array[index_row];
    pointer_array[index_row] = pointer_array[index_row + 1];
    pointer_array[index_row + 1] = temp_pointer;
}

void product_of_elements(int matrix[][MAX_MATRIX_SIZE], 
    int *const array_of_product, const int columns, const int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int product_of_elements = 1;

        for (int j = 0; j < columns; j++)
        {
            product_of_elements *= matrix[i][j];
        }

        array_of_product[i] = product_of_elements;
    }
}

void sort_by_product_of_elements(int **const pointer_array,
    int *const array_of_product, const int rows, const int columns)
{
    for (int i = 0; i < (rows - 1); i++)
    {
        for (int j = 0; j < (rows - i - 1); j++)
        {
            if (array_of_product[j] > array_of_product[j + 1])
            {
                int temp = array_of_product[j];
                array_of_product[j] = array_of_product[j + 1];
                array_of_product[j + 1] = temp;
                sort_pointers(pointer_array, j);
            }
        }
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

void filling_array_of_pointers(int matrix[][MAX_MATRIX_SIZE], 
    int **const array_of_pointers, const int rows)
{
    for (int i = 0; i < rows; i++)
    {
        array_of_pointers[i] = &matrix[i][0];
    }
}

void print_array(int **const matrix, const int rows, const int columns)
{
    puts("Formed matrix: ");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = { 0 };
    int array_of_product[MAX_MATRIX_SIZE] = { 0 };
    int *pointer_array[MAX_MATRIX_SIZE] = { NULL };
    int rows, columns;

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
    
    filling_array_of_pointers(matrix, pointer_array, rows);
    product_of_elements(matrix, array_of_product, columns, rows);
    sort_by_product_of_elements(pointer_array, array_of_product, rows, columns);
    print_array(pointer_array, rows, columns);

    return OK;
}

