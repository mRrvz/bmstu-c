#ifndef __LIST_OPERATIONS_H__
#define __LIST_OPERATIONS_H__

#include <stdio.h>
#include "struct.h"

int create_string_list(const char *string, node_t **head);

void print_list(FILE *f, const node_t *head);

void free_list(node_t *head);

#endif
