#include <stdio.h>

#define COUNT_READED 1
#define FILE_IS_EMPTY -1
#define ERROR_INPUT -2
#define NO_NUMBERS -3
#define OK 0

int count_avg_sum(FILE *const f, double *const avg_sum, int *const count_numbers)
{
    double curr_numb = 0;
    while (!feof(f))
    {
        if (fscanf(f, "%lf", &curr_numb) != COUNT_READED)
        {
            return ERROR_INPUT;
        }
        *avg_sum += curr_numb;
        ++(*count_numbers);
    }
    
    if (0 == (*count_numbers))
    {
        return NO_NUMBERS;
    }
    *avg_sum /= *count_numbers;

    return OK;
}

int count_dispersion(FILE *const f, double *const dispersion, double *const avg_sum, const int count_numbers)
{
    double curr_numb = 0; 

    while (!feof(f))
    {
        if (fscanf(f, "%lf", &curr_numb) != COUNT_READED)
        {
            return ERROR_INPUT;
        }
        *dispersion += (curr_numb - *avg_sum) * (curr_numb - *avg_sum) / count_numbers;
    }

    return OK;
}

int main(const int argc, const char *const argv[])
{
    setbuf(stdout, NULL);
     
    double avg_sum = 0;
    double dispersion = 0; 
    int count_numbers = 0;

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        puts("File is empty");
        return FILE_IS_EMPTY;
    }

    int code_error = count_avg_sum(f, &avg_sum, &count_numbers);
    if (code_error != OK)
    {
        return code_error;
    }

    fseek(f, 0, SEEK_SET);

    code_error = count_dispersion(f, &dispersion, &avg_sum, count_numbers);
    if (code_error != OK)
    {
        return code_error;
    }
    printf("Dispersion is: %lf", dispersion);
    
    fclose(f);
    return OK;
}

