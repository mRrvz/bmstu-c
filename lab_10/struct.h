#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef enum boolean
{
    false = 0,
    true = 1
} bool;

typedef struct product
{
    char *article;
    char *name;
    int count;
} product_t;

typedef struct product_arr
{
    product_t *array;
    int curr_size;
    int curr_memory;
} product_array_t;

#endif
