#include <stdio.h>

#define OK 0
#define INPUT_ERR 1
#define SIZE_ERR 2

#define TRUE 1
#define FALSE 0
#define OK_COUNT 1
#define NO_WORDS 2
#define ERROR_WORD_SIZE 3
#define EMPTY_STRING 4

#define MAX_LEN_WORD 16
#define SEP_SIZE 8
#define N 256

int my_strcmp(const char *const string1, const char *const string2)
{
    int i = 0;
    while (string1[i]) 
    {
        if (string1[i] != string2[i])
        {
            return FALSE;
        }
        ++i;
    }
    if (string2[i] != '\0')
    {
        return FALSE;
    }

    return TRUE;
}

int check_duplicate(char matrix[][N], const int len, const char *const string, const int index)
{
    for (int i = 0; i < len; i++)
    {
        if (my_strcmp(string, matrix[i]))
        {
            if (index == i)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }

    return TRUE; 
}

void lexem_repeat_search(char matrix1[][N], const int len_matrix1, char matrix2[][N], const int len_matrix2)
{
    puts("Result: ");
    for (int i = 0; i < len_matrix1; i++)
    {
        if (check_duplicate(matrix1, len_matrix1, matrix1[i], i))
        {
            int j = 0;
            int line_entry = FALSE;
            while (!line_entry && j < len_matrix2)
            {
                line_entry = my_strcmp(matrix1[i], matrix2[j]);
                ++j;
            }
        
            if (line_entry)
            {
                printf("%s yes\n", matrix1[i]);
            }
            else
            {
                printf("%s no\n", matrix1[i]);
            } 
        }
    }
}

int symb_check_separators(const char symbol)
{
    char separators[SEP_SIZE] = { ' ', ',', ';', ':', '.', '-', '!', '?' };
    for (int i = 0; i < SEP_SIZE; i++)
    {
        if (symbol == separators[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

int my_split(const char *const string, char matrix_split[][N], int *const count_lexem)
{
    int i = 0, k = 0;
    while (string[i + 1])
    {   
        if (!symb_check_separators(string[i]))
        {
            if (k >= MAX_LEN_WORD)
            {
                return ERROR_WORD_SIZE;
            }
            matrix_split[*count_lexem][k] = string[i];
            k++;
        }
        else
        {
            if (!symb_check_separators(string[i + 1]))
            {
                if (k != 0)
                {
                    ++(*count_lexem);
                    matrix_split[*count_lexem][k + 1] = '\0';
                }
                k = 0;
            }
        }
        ++i;
    }   

    if (!symb_check_separators(string[i]))
    {
        matrix_split[*count_lexem][k] = string[i];
        matrix_split[*count_lexem][++k] = '\0';
        if (k > MAX_LEN_WORD)
        {
            return ERROR_WORD_SIZE;
        }
    }

    if (*count_lexem != 0 || k > 0)
    {
        ++(*count_lexem);
    }

    return OK;
}

int readstring(char *const array)
{
    int i = 0;
    puts("Enter string: ");

    do
    {
        if (scanf("%c", &array[i]) != OK_COUNT)
        {
            return INPUT_ERR;
        }
        ++i;
    } while (array[i - 1] != '\n' && i <= N);
    
    if (array[i - 1] != '\n')
    {
        return SIZE_ERR;
    }

    if (i == 1)
    {
        return EMPTY_STRING;
    }
    array[i - 1] = '\0';

    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);
    char str1[N] = { 0 };
    char str2[N] = { 0 };
    int len_str1 = 0;
    int len_str2 = 0;
    int *pointer_len = &len_str1;

    char lexem_matrix1[N][N] = { 0 };
    char lexem_matrix2[N][N] = { 0 };
    const int str1_check = readstring(str1);
    const int str2_check = readstring(str2);
   
    if (str1_check != OK)
    {
        puts("Incorrect entered string1.");
        return str1_check;
    }
    
    if (str2_check != OK)
    {
        puts("Incorrect entered string2.");
        return str2_check;
    }

    const int len_words_check1 = my_split(str1, lexem_matrix1, pointer_len);
    pointer_len = &len_str2;
    const int len_words_check2 = my_split(str2, lexem_matrix2, pointer_len);

    if (len_words_check1 != OK || len_words_check2 != OK)
    {
        puts("One of the words is more than 16 symbols.");
        return ERROR_WORD_SIZE;
    }
    if (0 == len_str1 || 0 == len_str2)
    {
        puts("One of the string have no words");
        return NO_WORDS;
    }
    lexem_repeat_search(lexem_matrix1, len_str1, lexem_matrix2, len_str2);

    return OK;
}

