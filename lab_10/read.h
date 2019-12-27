#ifndef __READ_H__
#define __READ_H__

#include "struct.h"

int read_products(product_array_t *const products, FILE *f);

int read_sort_key(char *key, FILE *f);

#endif
