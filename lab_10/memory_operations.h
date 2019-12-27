#ifndef __MEMORY_OPERATIONS_H__
#define __MEMORY_OPERATIONS_H__

#include <stdlib.h>
#include "struct.h"

#define INVALID_MEMORY 3

int change_memory(void **products, const int size, size_t memory_size);

void free_products(product_array_t products);

void null_pointers(product_t *product, const int start, const int finish);

void init_array(product_array_t *const array, product_t *ptr);

#endif
