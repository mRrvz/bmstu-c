#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef enum boolean
{
    false = 0,
    true = 1
} bool;

typedef struct node
{
    char *part_of_string;
    struct node *next_node;
} node_t;

typedef struct
{
    char *value;
    int key;
} keys_table_t;

#endif
