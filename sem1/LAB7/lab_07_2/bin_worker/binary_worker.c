#include <stdio.h>
#include <string.h>

#define READED 1
#define OK 0
#define READ_ERROR 1
#define WRITE_ERROR 1
#define INDEX_ERROR -2
#define FILE_ERROR -3

typedef struct
{
    char name[31];
    char manufactor[16];
    unsigned int price;
    unsigned int count;
} product;


void print_product(const product item)
{
    printf("Product %s:\n", item.name);
    printf("\tManufacturer: %s\n", item.manufactor);
    printf("\tPrice: %u\n", item.price);
    printf("\tCount: %u\n", item.count);
}


int get_by_pos(FILE *const f, const int pos, product *const item)
{
    if (!f)
    return FILE_ERROR;

    fseek(f, pos * sizeof(product), SEEK_SET);

    if (fread(item, sizeof(product), 1, f) == READED)
        return OK;
    return READ_ERROR;
}


int put_by_pos(FILE *const f, const int pos, const product item)
{
    if (!f)
    return FILE_ERROR;

    fseek(f, sizeof(product) * pos, SEEK_SET);
    if (ftell(f) != sizeof(product) * pos)
        return INDEX_ERROR;

    if (fwrite(&item, sizeof(product), 1, f) != READED)
        return WRITE_ERROR;
    return OK;
}


void show_all(FILE *const f)
{
    product item;
    for (int i = 0; get_by_pos(f, i, &item) == OK; i++)
    {
        print_product(item);
        printf("\n");
    }
}


void insert_end(FILE *const f, const product item)
{
    int pos;
    fseek(f, 0, SEEK_END);
    pos = ftell(f) / sizeof(product);
    put_by_pos(f, pos, item);
}


int from_user(product *item)
{
    int rc;
    printf("Enter name: ");
    rc = scanf("%s", item->name);
    printf("Enter manufactorer: ");
    rc += scanf("%s", item->manufactor);
    printf("Enter price: ");
    rc += scanf("%u", &(item->price));
    printf("Enter count: ");
    rc += scanf("%u", &(item->count));
    return (rc == 4) ? OK : READ_ERROR;
}


int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    FILE *f;

    if (argc == 3 && !strcmp(argv[1], "ins"))
    {
        f = fopen(argv[2], "r+");
        product item;
        from_user(&item);
        insert_end(f, item);
        fclose(f);
        printf("Info was added.");
        return 0;
    }

    else if (argc == 3 && !strcmp("show", argv[1]))
    {
        f = fopen(argv[2], "r");
        show_all(f);
        fclose(f);
        return 0;
    }

    printf("Bad call!");
    return 0;
}
