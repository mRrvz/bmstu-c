#include "operations.h"
#include "comparators.h"
#include "memory_operations.h"
#include "string.h"
#include "struct.h"

#define ARTICLE "ARTCILE"
#define NAME "NAME"
#define DELETE_PARAM "LIPSTICK"

#define OK 0
#define ARRAY_IS_EMPTY 8

static void delete_product(product_t *array, const int pos, const int size)
{
    free(array[pos].article);
    free(array[pos].name);

    for (int i = pos; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }

    array[size - 1].article = NULL;
    array[size - 1].name = NULL;
}

int delete_elements(product_array_t *const products)
{
    for (int i = 0; i < products->curr_size; i++)
    {
        if (0 == products->array[i].count && !strcmp(products->array[i].article, DELETE_PARAM))
        {
            delete_product(products->array, i, products->curr_size);
            products->curr_size--;
            i--;
        }
    }

    if (0 == products->curr_size)
    {
        return ARRAY_IS_EMPTY;
    }

    return OK;
}

static int brand_length(const product_t products)
{
    // + 1 для терминального нуля
    return strlen(products.name) + strlen(products.article) + 1;
}

int update_article(product_array_t *const products)
{
    for (int i = 0; i < products->curr_size; i++)
    {
        if (change_memory((void **)&products->array[i].article, brand_length(products->array[i]), sizeof(char)))
        {
            return INVALID_MEMORY;
        }

        strcat(products->array[i].article, products->array[i].name);
    }

    return OK;
}

static void my_qsort(product_array_t *const products, int start, int end, int (*comparator) (const void *, const void *))
{
    product_t start_temp, end_temp, pivot_temp;
    int i, j, pivot;

    if (start < end)
    {
        pivot = (start + end) / 2;
        i = start;
        j = end;

        while (i < j)
        {
            start_temp = products->array[i];
            end_temp = products->array[j];
            pivot_temp = products->array[pivot];

            while ((*comparator)(&start_temp, &pivot_temp) <= 0 && i < end)
            {
                start_temp = products->array[++i];
            }

            while ((*comparator)(&end_temp, &pivot_temp) > 0)
            {
                end_temp = products->array[--j];
            }

            if (i < j)
            {
                products->array[i] = end_temp;
                products->array[j] = start_temp;
            }
        }

        products->array[pivot] = end_temp;
        products->array[j] = pivot_temp;

        my_qsort(products, start, i - 1, comparator);
        my_qsort(products, j + 1, end, comparator);
    }
}

void sort_products(product_array_t *const products, const char *const key)
{
    if (!strcmp(key, ARTICLE))
    {
        my_qsort(products, 0, products->curr_size - 1, article_comparator);
    }
    else
    {
        if (!strcmp(key, NAME))
        {
            my_qsort(products, 0, products->curr_size - 1, name_comparator);
        }
        else
        {
            my_qsort(products, 0, products->curr_size - 1, count_comparator);
        }
    }
}
