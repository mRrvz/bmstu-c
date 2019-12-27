#ifndef __MATRIX_STRUCT_H__
#define __MATRIX_STRUCT_H__

#include <inttypes.h>

typedef struct
{
    int64_t **matrix;
    int64_t column;
    int64_t row;
    int64_t degree;
} matrix_t;

#endif
