#include <stdio.h>

#define FILE_NAME "in.txt"
#define FILE_OUT "out.txt"

#define READ_ERR 3
#define SIZE_ERR 2
#define FILE_ERR 1
#define OK 0

#define M 100
#define N 11
#define COUNT_READED 1

#define TRUE 1
#define FALSE 0

void writefile(FILE *const f, const char *const string, const int len)
{
    for (int i = (len - 1); i >= 0; i--)
    {
        fprintf(f, "%c", string[i]);
    }
}

int read_lex(FILE *const f, int *const size, int *const curr, int *const EOF_checker)
{
    char string[N];
    int i = -1;
    do
    {
        ++i;
        if (i > (N - 1))
        {
            return SIZE_ERR;
        }

        int code = fscanf(f, "%c", &string[i]);
        if (code == EOF)
        {
            *EOF_checker = TRUE;
            break;
        }
        if (code != COUNT_READED)
        {
            return READ_ERR;
        }
    }
    while (string[i] != ' ' && string[i] != '\n');

    string[i] = '\0'; 
    fseek(f, *curr, SEEK_SET); 
    writefile(f, string, i);
    *curr += i;
    *size = i;

    return OK;
}

void write_size(FILE *const f1, const int size, const int spaces)
{
    if (size != 0 && spaces != 0)
    {
        fprintf(f1, "%d", size);
        for (int i = 0; i < spaces; i++)
        {
            fprintf(f1, "%c", ' ');
        }

        return;
    }

    fprintf(f1, "%c", '\n');
}

int check_spaces(FILE *const f, FILE *const f1, const int size, int *const curr)
{
    char checker;
    int i = 0;
    do 
    {
        ++i;
        if (fscanf(f, "%c", &checker) != COUNT_READED)
        {
            return READ_ERR;
        }
    }
    while (checker == ' ' && checker != '\n');
    fseek(f, *curr + i, SEEK_SET);
    *curr += i;
    write_size(f1, size, i);

    return OK;
}

int pars_lex(FILE *const f, FILE *const f1)
{
    int curr = 0;
    int EOF_checker = FALSE;
    while (!feof(f))
    {
        int size = 0;
        if (read_lex(f, &size, &curr, &EOF_checker))
        {
            return READ_ERR;
        }
        if (EOF_checker)
        {
            write_size(f1, size, 1);
            return OK;
        }
        if (check_spaces(f, f1, size, &curr))
        {
            return READ_ERR;
        }
    }

    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);
    FILE *f;
    FILE *f1;

    if ((f = fopen(FILE_NAME, "r+")) == NULL)
    {
        puts("File in.txt error");
        return FILE_ERR;
    }
    if ((f1 = fopen(FILE_OUT, "w")) == NULL)
    {
        puts("File out.txt error");
        return FILE_ERR;
    }
    
    if (pars_lex(f, f1))
    {
        return READ_ERR;
    }
    fclose(f);
    fclose(f1);

    puts("Lexem reversed");
    return OK;
}
