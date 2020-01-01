#ifndef __STRING_OPERATIONS_H__
#define __STRING_OPERATIONS_H__

#include <stdio.h>
#include "struct.h"

#define BAD_KEY -1
#define OUT_STRING 0
#define DOUBLE_SPACES_DELETE 1
#define CONCAT_STRINGS 2
#define FIND_SUBSTRING 3

int key_from_string(const char *const string);

int concat_strings(node_t *first_list_head, node_t *second_list_head);

void delete_double_spaces(node_t *list_head);

int find_substring(node_t *first_list_head, node_t *second_list_head);

int get_line(FILE *f, int maxsize, char *string);

#endif
