#include <stdio.h>

#include "print.h"
#include "matrix_struct.h"

void print_result(const matrix_t matrix)
{
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.column; j++)
        {
            printf("%"PRId64" ", matrix.matrix[i][j]);
        }

        putchar('\n');
    }
}
