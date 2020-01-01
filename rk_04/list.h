#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct list
{
    char character;
    struct list *next_node;
} node_t;

node_t *create_list(void);

void print_list(FILE *f, const node_t *tail);

void free_list(node_t *head);

#endif
