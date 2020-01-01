#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <stdio.h>
#include "struct.h"

int parsing_file(FILE *f, words_t *unique_words, string_t **string_array, int *array_size);

int comparator(const void *str1, const void *str2);

void format_binary_array(words_t unique_words, string_t *string_array, int array_size);

void print_binary_to_file(FILE *f, string_t *string_array, int array_size);

void find_words(string_t *string_array, int array_size, int binary_arr_size, int *i_max, int *j_max);

void print_words_to_file(FILE *f, string_t *string_array, int i_max, int j_max);

#endif
