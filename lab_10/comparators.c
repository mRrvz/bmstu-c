#include "comparators.h"
#include "struct.h"
#include "string.h"

int article_comparator(const void *element1, const void *element2)
{
    return strcmp(((product_t *)element1)->article, ((product_t *)element2)->article);
}

int name_comparator(const void *element1, const void *element2)
{
    return strcmp(((product_t *)element1)->name, ((product_t *)element2)->name);
}

int count_comparator(const void *element1, const void *element2)
{
    return ((product_t *)element1)->count - ((product_t *)element2)->count;
}
