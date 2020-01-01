#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operations.h"

#define OK 0
#define INVALID_MEMORY 2
#define N 101

void print_words_to_file(FILE *f, string_t *string_array, int i_max, int j_max)
{
    fprintf(f, "%s\n", "Максимально похожие 2 предложения: \n");
    for (int i = 0; i < string_array[i_max].size; i++)
        fprintf(f, "%s ", string_array[i_max].words[i]);
    fprintf(f, "\n");

    for (int j = 0; j < string_array[j_max].size; j++)
        fprintf(f, "%s ", string_array[j_max].words[j]);
    fprintf(f, "\n");
}

void find_words(string_t *string_array, int array_size, int binary_arr_size, int *i_max, int *j_max)
{
    int scalar_max = 0;

    for (int i = 0; i < array_size; i++)
    {
        for (int j = i + 1; j < array_size; j++)
        {
            int scalar_current = 0;
            for (int k = 0; k < binary_arr_size; k++)
            {
                if (string_array[i].flag[k] == '1' && string_array[j].flag[k] == '1')
                {
                    scalar_current++;
                }
            }

            if (scalar_current > scalar_max)
            {
                *i_max = i;
                *j_max = j;
                scalar_max = scalar_current;
            }
        }
    }
}

void print_binary_to_file(FILE *f, string_t *string_array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        fprintf(f, "%s\n", string_array[i].flag);
    }
}

int comparator(const void *str1, const void *str2)
{
    return strcmp((char *)str1, (char *)str2);
}

static int change_memory(void **strings, const int size, size_t memory_size)
{
    void *new_ptr = realloc(*strings, size * memory_size);
    if (new_ptr == NULL)
    {
        return INVALID_MEMORY;
    }

    *strings = new_ptr;
    new_ptr = NULL;

    return OK;
}

static int check_in_array(words_t *unique_words, char *buff)
{
    for (int i = 0; i < unique_words->size; i++)
    {
        if (!strcmp(unique_words->words[i], buff))
        {
            return i;
        }
    }

    return -1;
}

int init_string_array_element(string_t **string_array, const int array_size)
{
    if (change_memory((void **)string_array, array_size, sizeof(string_t)))
    {
        return INVALID_MEMORY;
    }

    (*string_array)[array_size - 1].words = malloc(N * sizeof(char *));
    (*string_array)[array_size - 1].memory = N;
    (*string_array)[array_size - 1].size = 0;

    return OK;
}

void format_binary_array(words_t unique_words, string_t *string_array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        for (int j = 0; j < string_array[i].size; j++)
        {
            int index = check_in_array(&unique_words, string_array[i].words[j]);

            if (index != -1)
            {
                string_array[i].flag[index] = '1';
            }
        }
    }
}

int parsing_file(FILE *f, words_t *unique_words, string_t **string_array_copy, int *array_size)
{
    char buff[N];
    char c;

    unique_words->size = 0;
    unique_words->memory = 10;
    unique_words->words = malloc(10 * sizeof(char *));

    string_t *string_array = malloc(sizeof(string_t));
    init_string_array_element(&string_array, *array_size);

    if (string_array == NULL)
    {
        return INVALID_MEMORY;
    }

    if (unique_words->words == NULL)
    {
        return INVALID_MEMORY;
    }

    while ((fscanf(f, "%100s", buff) != EOF))
    {
        if ((unique_words->words[unique_words->size] = malloc(strlen(buff) + 1)) == NULL)
        {
            return INVALID_MEMORY;
        }

        if ((string_array[*array_size - 1].words[string_array[*array_size - 1].size] = malloc(strlen(buff) + 1)) == NULL)
        {
            return INVALID_MEMORY;
        }

        strcpy(string_array[*array_size - 1].words[string_array[*array_size - 1].size], buff);

        if (++string_array[*array_size - 1].size >= string_array[*array_size - 1].memory)
        {
            string_array[*array_size - 1].memory *= 2;
            if (change_memory((void **)string_array[*array_size - 1].words, string_array[*array_size - 1].memory, sizeof(char *)))
            {
                return INVALID_MEMORY;
            }
        }

        if (check_in_array(unique_words, buff) == -1)
        {
            strcpy(unique_words->words[unique_words->size++], buff);
        }

        if (unique_words->size >= unique_words->memory)
        {
            unique_words->memory *= 2;

            if (change_memory((void **)&unique_words->words, unique_words->memory, sizeof(char *)))
            {
                return INVALID_MEMORY;
            }
        }

        if ((c = fgetc(f)) == '\n')
        {
            (*array_size)++;
            init_string_array_element(&string_array, *array_size);
        }
    }

    (*array_size)--;

    for (int i = 0; i < *array_size; i++)
    {
        string_array[i].flag = malloc(unique_words->size * sizeof(char) + 1);
        memset(string_array[i].flag, '0', unique_words->size + 1);
        /*
        for (int j = 0; j < string_array[i].size; j++)
        {
            printf("%s ", string_array[i].words[j]);
        }
        putchar('\n');
        */
    }

    *string_array_copy  = string_array;

    return OK;
}
