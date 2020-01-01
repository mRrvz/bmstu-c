#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct
{
    char **words;
    int size;
    int memory;
    char *flag;
} string_t;

typedef struct words
{
    char **words;
    int size;
    int memory;
} words_t;

#endif
