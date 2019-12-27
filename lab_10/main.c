#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "memory_operations.h"
#include "operations.h"
#include "struct.h"
#include "print.h"

#define MAX_KEY 8
#define FILE_NAME "stockpile.txt"
#define START_MEMORY 10

#define OK 0
#define FILE_ERROR 8

int main(void)
{
    setbuf(stdout, NULL);

    char sort_key[MAX_KEY];
    FILE *f = NULL;
    FILE *stream = stdin;
    product_array_t product_array;
    product_t *products_ptr = NULL;
    int code_error;

    init_array(&product_array, products_ptr);

    if ((code_error = change_memory((void**)&product_array.array,
                                    product_array.curr_memory,
                                    sizeof(product_t))))
    {
        free_products(product_array);
        return code_error;
    }

    null_pointers(product_array.array, 0, product_array.curr_memory);

    if ((code_error = read_products(&product_array, stream)))
    {
        fprintf(stderr, "Invalid enter products.\n");
        free_products(product_array);
        return code_error;
    }

    if ((code_error = read_sort_key(sort_key, stream)))
    {
        fprintf(stderr, "Invalid key.\n");
        free_products(product_array);
        return code_error;
    }

    update_article(&product_array);

    if ((code_error = delete_elements(&product_array)))
    {
        fprintf(stderr, "Array is empty.\n");
        free_products(product_array);
        return code_error;
    }

    sort_products(&product_array, sort_key);

    if ((f = fopen(FILE_NAME, "w+")) == NULL)
    {
        free_products(product_array);
        return FILE_ERROR;
    }

    print_to_file(product_array, f);
    free_products(product_array);
    fclose(f);

    return OK;
}
