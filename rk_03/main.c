#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct.h"
#include "operations.h"

#define FILE_IN_NAME "in.txt"
#define FILE_OUT_NAME "out.txt"

#define OK 0
#define FILE_ERROR 1
#define MEMORY_ERROR 2

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    FILE *f;
    int code_error;

    words_t unique_words;
    string_t *strings_array = NULL;
    int array_size = 1;
    int i_max = 0, j_max = 1;

    if ((f = fopen(argv[1], "r+")) == NULL)
    {
        fprintf(stderr, "Invalid file.\n");
        return FILE_ERROR;
    }

    if ((code_error = parsing_file(f, &unique_words, &strings_array, &array_size)))
    {
        fprintf(stderr, "Parsing error.\n");
        return code_error;
    }

    qsort(unique_words.words, unique_words.size, sizeof(char *), comparator);
    /*
    for (int i = 0; i < unique_words.size; i++)
    {
        printf("%s ", unique_words.words[i]);
    }
    */

    format_binary_array(unique_words, strings_array, array_size);
    fclose(f);

    if ((f = fopen(FILE_OUT_NAME, "w+")) == NULL)
    {
        fprintf(stderr, "Invalid file.\n");
        return FILE_ERROR;
    }

    print_binary_to_file(f, strings_array, array_size);
    find_words(strings_array, array_size, strlen(strings_array[0].flag), &i_max, &j_max);
    print_words_to_file(f, strings_array, i_max, j_max);
    fclose(f);

    return OK;
}
