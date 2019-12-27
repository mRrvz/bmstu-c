#include <stdlib.h>
#include "memory_operations.h"

#define MEMORY_START 10

#define OK 0

int change_memory(void **products, const int size, size_t memory_size)
{
    void *new_ptr = realloc(*products, size * memory_size);
    if (new_ptr == NULL)
    {
        return INVALID_MEMORY;
    }

    *products = new_ptr;
    new_ptr = NULL;

    return OK;
}

void free_products(product_array_t products)
{
    for (int i = 0; i < products.curr_memory; i++)
    {
        if (products.array[i].article != NULL)
        {
            free(products.array[i].article);
        }

        if (products.array[i].name != NULL)
        {
            free(products.array[i].name);
        }
    }

    free(products.array);
}

void null_pointers(product_t *product, const int start, const int finish)
{
    for (int i = start; i < finish; i ++)
    {
        product[i].article = NULL;
        product[i].name = NULL;
    }
}

void init_array(product_array_t *const array, product_t *ptr)
{
    array->array = ptr;
    array->curr_size = 0;
    array->curr_memory = MEMORY_START;
}
