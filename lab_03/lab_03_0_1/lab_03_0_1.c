#include <stdio.h>

#define COUNT_READED 1
#define INPUT_ERR -1
#define NO_NEGATIVE_NUMBERS -2
#define FILE_IS_EMPTY -3
#define OK 0

int read_and_count(FILE *const f, int *const pointer_numb)
{
    int numb_previous = 0;
    int numb = 0;
    int max_numb = 0;

    if (feof(f))
    {
        return FILE_IS_EMPTY;
    }

    while (!feof(f))
    {
        if (fscanf(f, "%d", &numb) != COUNT_READED)
        {
            return INPUT_ERR;
        }

        if (numb_previous < 0 && numb > max_numb)
        {
            max_numb = numb; 
        }

        numb_previous = numb;
    }

    if (0 == max_numb)
    {
        return NO_NEGATIVE_NUMBERS;
    }
    *pointer_numb = max_numb;

    return OK; 
}

int main(void)
{
    int max_numb = 0;
    const int code_error = read_and_count(stdin, &max_numb);

    if (code_error != OK)
    {
        return code_error;
    }
    printf("Max number after negative numbers ins: %d", max_numb);

    return OK;
}

