#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "read.h"
#include "memory_operations.h"
#include "struct.h"

#define READ_OK 1
#define END_ENTER "nothing"
#define N 256

#define ARTICLE "ARTICLE"
#define NAME "NAME"
#define COUNT "COUNT"

#define OK 0
#define INVALID_INPUT 1
#define INVALID_COUNT 2
#define NEGATIVE_COUNT 4
#define INVALID_SIZES 5
#define LOWER_ARTICLE 6
#define INVALID_KEY 7

static int check_upper(const char *str)
{
    while (*str)
    {
        if (!isupper(*str))
        {
            return false;
        }

        ++str;
    }

    return true;
}

int read_products(product_array_t *const products, FILE *f)
{
    char article_checker[N];
    char name_checker[N];
    int i = 0;

    while (true)
    {
        puts("Enter article: ");
        if (fscanf(f, "%256s", article_checker) != READ_OK)
        {
            return INVALID_INPUT;
        }

        // проверка, что ввод закончен
        if (!strcmp(article_checker, END_ENTER))
        {
            if (i == 0)
            {
                return INVALID_SIZES;
            }

            products->curr_size = i;
            return OK;
        }

        // проверка, что артикл введен полностью заглавными
        if (!check_upper(article_checker))
        {
            return LOWER_ARTICLE;
        }

        // если не хватает выделенной памяти, увеличивается вдвое
        if (i >= products->curr_memory)
        {
            products->curr_memory *= 2;

            if (change_memory((void**)&products, products->curr_memory, sizeof(product_t)))
            {
                return INVALID_MEMORY;
            }

            // зануление указателей, для которых еще не выделена память
            null_pointers(products->array, products->curr_memory / 2, products->curr_memory);
        }

        // + 1 для терминального нуля
        if (change_memory((void**)&products->array[i].article, strlen(article_checker) + 1, sizeof(char)))
        {
            return INVALID_MEMORY;
        }

        strcpy(products->array[i].article, article_checker);

        puts("Enter name: ");
        if (fscanf(f, "%256s", name_checker) != READ_OK)
        {
            return INVALID_INPUT;
        }

        if (change_memory((void**)&products->array[i].name, strlen(name_checker) + 1, sizeof(char)))
        {
            return INVALID_MEMORY;
        }

        strcpy(products->array[i].name, name_checker);

        puts("Enter count: ");
        if (fscanf(f, "%d", &products->array[i].count) != READ_OK)
        {
            return INVALID_INPUT;
        }

        if (products->array[i].count < 0)
        {
            fprintf(stderr, "Count should be >= 0\n");
            return NEGATIVE_COUNT;
        }

        i++;
    }
}

int read_sort_key(char *key, FILE *f)
{
    puts("Enter sort key: ");
    if (fscanf(f, "%8s", key) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (strcmp(key, ARTICLE) && strcmp(key, NAME) && strcmp(key, COUNT))
    {
        return INVALID_KEY;
    }

    return OK;
}
