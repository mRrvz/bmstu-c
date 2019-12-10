#include <stdio.h>
#define MIN_MATRIX_SIZE 1
#define MAX_MATRIX_SIZE 10

#define OK 0
#define ERROR_SIZE_INPUT 1
#define ROWS_ERROR_INPUT 2
#define COLUMNS_ERROR_INPUT 3
#define ELEMENTS_MATRIX_INPUT_ERROR 4

#define INCORRECT_ROW 1
#define COUNT_CORRECT_ELEMENTS_MATRIX 1
#define COUNT_CORRECT_VARIABLES 2
#define WRONG_COLUMN 0
#define CORRECT_COLUMN 1

void alternation_of_elements(int matrix[][MAX_MATRIX_SIZE], const int rows, const int columns, int *const array)
{
    int count_various_sign;

    for (int j = 0; j < columns; j++)
    {
        count_various_sign = 0;
        for (int i = 0; i < (rows - 1); i++)
        {
            if (matrix[i][j] * matrix[i + 1][j] < 0)
            {
                count_various_sign++;
            }
        }

        if ((count_various_sign + 1) == rows && rows != INCORRECT_ROW)
        {
            array[j] = CORRECT_COLUMN;
        }
        else
        {
            array[j] = WRONG_COLUMN;
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

void print_array(const int *const array, const int size_array)
{
    puts("Formed array: ");
    for (int i = 0; i < size_array; i++)
    {
        printf("%d ", array[i]);
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = { 0 };
    int array[MAX_MATRIX_SIZE] = { 0 };
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

    alternation_of_elements(matrix, rows, columns, array);
    print_array(array, columns);

    return OK;
}
