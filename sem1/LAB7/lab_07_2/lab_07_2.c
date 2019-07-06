#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NAME_SIZE 31
#define MANUF_SIZE 16
#define COUNT_WRITE 1
#define COUNT_READED 1
#define MIN_ARGS 3
#define FILE_NAME 2
#define KEY_ARGS 1
#define N 100
#define M 4

#define ERROR_ARGS 53
#define FILE_ERR 1
#define ERR_INPUT 2
#define GET_ERR 3
#define PUT_ERR 4
#define EMPTY_FILE 5
#define NO_SUBSTR 6
#define OK 0

#define TRUE 1
#define FALSE 0

typedef struct
{
    char name[NAME_SIZE];
    char manafacturer[MANUF_SIZE];
    uint32_t price;
    uint32_t count;
} product_t;

int size_counter(FILE *const f)
{    
    fseek(f, 0, SEEK_END);
    int size = ftell(f) / sizeof(product_t);
    fseek(f, 0, SEEK_SET);

    return size;
}

int get_by_pos(FILE *const f, const int pos, product_t *const product_list)
{
    fseek(f, pos * sizeof((*product_list)) - sizeof((*product_list)), SEEK_SET);
    if (fread(product_list, sizeof((*product_list)), COUNT_READED, f) != COUNT_READED)
    {
        return GET_ERR;
    }
    return OK;
}

int put_by_pos(FILE *const f, const int pos, const product_t product_list)
{
    fseek(f, pos * sizeof(product_list) - sizeof(product_list), SEEK_SET);
    if (fwrite(&product_list, sizeof(product_list), COUNT_WRITE, f) != COUNT_WRITE)
    {
        return PUT_ERR;
    }
    return OK;
}

int copy_file(FILE *const f1, FILE *const f2)
{
    product_t product;
    int size = size_counter(f1);

    for (int i = 1; i <= size; i++)
    {
        if (get_by_pos(f1, i, &product) != OK)
        {
            return GET_ERR;
        }
        if (put_by_pos(f2, i, product) != OK)
        {
            return PUT_ERR;
        }
    }

    return OK;
}

int sort_file(FILE *const f)
{
    product_t pr1, pr2, temp;
    const int size = size_counter(f);

    for (int i = 1; i < size; i++)
    {
        int min_ind = i;
        for (int j = i + 1; j <= size; j++)
        {
            if (get_by_pos(f, j, &pr1) != OK)
            {
                return GET_ERR;
            }
            if (get_by_pos(f, min_ind, &pr2) != OK)
            {
                return GET_ERR;
            }

            if (pr1.price > pr2.price)
            {
                min_ind = j;
            }
            if (pr1.price == pr2.price)
            {
                if (pr1.count > pr2.count)
                {
                    min_ind = j;
                }
            }
        }
        if (get_by_pos(f, i, &temp) != OK)
        {
            return GET_ERR;
        }
        if (get_by_pos(f, min_ind, &pr1) != OK)
        {
            return GET_ERR;
        }

        if (put_by_pos(f, i, pr1) != OK)
        {
            return PUT_ERR;
        }
        if (put_by_pos(f, min_ind, temp) != OK)
        {
            return PUT_ERR;
        }
    }

    return OK;
}

int check_substr(const char *const name, const char *const substr)
{
    int len_name = strlen(name) - 1;
    int len_substr = strlen(substr) - 1;
    
    while (len_substr >= 0)
    {
        if (name[len_name] != substr[len_substr])
        {
            return FALSE;
        }
        --len_substr;
        --len_name;
    }

    return TRUE;
}


void printstruct(const product_t product)
{
    printf("%s\n", product.name);
    printf("%s\n", product.manafacturer);
    printf("%u\n", product.price);
    printf("%u\n", product.count);
}

void print_file(FILE *const f)
{
    product_t temp_struct;
    fseek(f, 0, SEEK_SET);
    while (fread(&temp_struct, sizeof(temp_struct), 1, f))
    {
        printstruct(temp_struct);
    }
}

int info_items(FILE *const f, const char *const substr)
{
    product_t product;
    int count = 0;
    const int size = size_counter(f);

    for (int i = 1; i <= size; i++) 
    {
        if (get_by_pos(f, i, &product) != OK)
        {
            return GET_ERR;
        }

        if (check_substr(product.name, substr))
        {
            ++count;
            printstruct(product);
        }
    }

    if (0 == count)
    {
        return NO_SUBSTR;
    }

    return OK;
}

int add_info(FILE *const f, const product_t temp)
{
    product_t prod;
    const int size = size_counter(f);
    int pos = 1;

    for (int i = 1; i <= size; i++)
    {
        if (get_by_pos(f, i, &prod) != OK)
        {
            return GET_ERR;
        }

        if ((temp.price == prod.price && temp.count > prod.count) || (temp.price > prod.price))
        {
            break;
        }
        ++pos;
    }
    
    for (int i = size; i >= pos; i--)
    {
        if (get_by_pos(f, i, &prod) != OK)
        {
            return GET_ERR;
        }
        if (put_by_pos(f, (i + 1), prod) != OK)
        {
            return PUT_ERR;
        }
    }

    if (put_by_pos(f, pos, temp) != OK)
    {
        return PUT_ERR;
    }
    
   return OK;
}

int enter_structure(FILE *const f)
{
    product_t temp_struct;
    memset(&temp_struct, 0, sizeof(product_t));
    puts("Enter name: ");
    if (scanf("%s", temp_struct.name) != COUNT_READED)
    {
        return ERR_INPUT;
    }
    puts("Enter manafacturer: ");
    if (scanf("%s", temp_struct.manafacturer) != COUNT_READED)
    {
        return ERR_INPUT;
    }
    puts("Enter price: ");
    if (scanf("%u", &temp_struct.price) != COUNT_READED)
    {
        return ERR_INPUT;
    }
    puts("Enter count: ");
    if (scanf("%u", &temp_struct.count) != COUNT_READED)
    {
        return ERR_INPUT;
    }

    int code_err = add_info(f, temp_struct);
    if (code_err != OK)
    {
        return code_err;
    }

    return OK;
}

int check_size(FILE *const f)
{
    const int size = size_counter(f);
    if (0 == size)
    {
        puts("File is empty");
        return EMPTY_FILE;
    }
    return OK;
}

int main(const int argc, const char *const argv[])
{
    setbuf(stdout, NULL);
    FILE *f; 

    if (argc < MIN_ARGS)
    {
        puts("Invalid args!");
        return ERROR_ARGS;
    }

    if (!strcmp(argv[KEY_ARGS], "sb"))
    {
        FILE *f1;
        if (argc < MIN_ARGS + 1 || argv[FILE_NAME + 1] == NULL)
        {
            puts("Invalid args!");
            return ERROR_ARGS;
        }
        if ((f1 = fopen(argv[FILE_NAME + 1], "w+b")) == NULL || (f = fopen(argv[FILE_NAME], "rb")) == NULL)
        {
            puts("Cant open file");
            return FILE_ERR;
        }
        if (check_size(f))
        {
            fclose(f);
            return EMPTY_FILE;
        }

        int code_err = copy_file(f, f1);
        if (code_err != OK)
        {
            fclose(f);
            fclose(f1);
            return code_err;
        }
        code_err = sort_file(f1);
        if (code_err != OK)
        {
            fclose(f);
            fclose(f1);
            return code_err;
        }

        print_file(f1);
        fclose(f);
        fclose(f1);

        return OK;
    }

    if (!strcmp(argv[KEY_ARGS], "fb"))
    {
        if (argc < MIN_ARGS + 1 || argv[FILE_NAME + 1] == NULL)
        {
            puts("Invalid args!");
            return ERROR_ARGS;
        }

        if ((f = fopen(argv[FILE_NAME], "rb")) == NULL)
        {
            puts("Cant open file");
            return FILE_ERR;
        }

        if (check_size(f))
        {
            fclose(f);
            return EMPTY_FILE;
        }

        const int code_err = info_items(f, argv[FILE_NAME + 1]);
        if (code_err != OK)
        {
            fclose(f);
            return code_err;
        }
        fclose(f);

        return OK; 
    }

    if (!strcmp(argv[KEY_ARGS], "ab"))
    {
        if ((f = fopen(argv[FILE_NAME], "r+b")) == NULL)
        {
            puts("Cant open file");
            return FILE_ERR;
        }
        
        if (check_size(f))
        {
            fclose(f);
            return EMPTY_FILE;
        }

        const int code_err = enter_structure(f);
        if (code_err != OK)
        {
            fclose(f);
            return code_err;
        }
        puts("Info was added");
        fclose(f);

        return OK;
    }

    return ERROR_ARGS;    
}
