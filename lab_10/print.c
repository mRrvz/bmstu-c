#include <stdio.h>
#include "print.h"

void print_to_file(product_array_t products, FILE *f)
{
    for (int i = 0; i < products.curr_size; i++)
    {
        fprintf(f, "%s\n", products.array[i].article);
        fprintf(f, "%s\n", products.array[i].name);
        fprintf(f, "%d\n", products.array[i].count);
    }
}
