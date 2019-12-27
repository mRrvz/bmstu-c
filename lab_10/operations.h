#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "struct.h"

int delete_elements(product_array_t *const products);

int update_article(product_array_t *const products);

void sort_products(product_array_t *const products, const char *const key);

#endif
