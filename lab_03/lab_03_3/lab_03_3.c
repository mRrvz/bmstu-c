/* Данная программа может создать бинарный файл, отсортировать его по возрастанию его элементов,
 * а так же заполнить его 20 случайными числами в диапазоне от 0 до 100. Сортировка реализована 
 * с помощью алгоритма сортировки выбором. */ 

#include <stdio.h>
#include <stdlib.h>

#define RANDOM_COUNT_NUMB 20
#define N 100
#define CORR_COUNT_ARGS 3
#define WRITE_COUNT 1
#define COUNT_READED 1
#define TOKEN 1
#define FILE_NAME 2

#define INVALID_COUNT_ARGS 1
#define INCORRECT_TOKEN 2
#define FILE_IS_EMPTY 3
#define OK 0


int get_number_by_pos(FILE *const f, const int pos)
{
    int numb;
    fseek(f, pos * sizeof(int) - sizeof(int), SEEK_SET);
    fread(&numb, sizeof(int), COUNT_READED, f);
    return numb;
}

void put_number_by_pos(FILE *const f, const int pos, const int numb)
{
    fseek(f, pos * sizeof(int) - sizeof(int), SEEK_SET);
    fwrite(&numb, sizeof(int), WRITE_COUNT, f);
}

// Сортировка файла по возрастанию элементов с помощью сортировки выбором
void sort_file(FILE *const f, const int size)
{
    for (int i = 1; i < size; i++)
    {
        int index_min_elem = i;
        for (int j = i + 1; j <= size; j++)
        {
            const int curr_numb = get_number_by_pos(f, j);
            const int min_index_numb = get_number_by_pos(f, index_min_elem);
            if (curr_numb < min_index_numb)
            {
                index_min_elem = j;
            }
        }
        const int temp = get_number_by_pos(f, i);
        const int curr_numb = get_number_by_pos(f, index_min_elem);
        put_number_by_pos(f, i, curr_numb);
        put_number_by_pos(f, index_min_elem, temp); 
    }
}

int print_file(FILE *const f)
{
    int temp_numb = 0;
    int count = 0;

    while (fread(&temp_numb, sizeof(int), COUNT_READED, f) == COUNT_READED)
    {
        printf("%d ", temp_numb);
        ++count;
    }
    return count;
}

int numb_counter(FILE *const f)
{
    int count = 0;
    int temp_numb;
    while (fread(&temp_numb, sizeof(int), COUNT_READED, f) == COUNT_READED)
    {
        ++count;
    }
    fseek(f, 0, SEEK_SET);
    return count;
}

void create_file(FILE *const f)
{
    for (int i = 0; i < RANDOM_COUNT_NUMB; i++)
    {
        const int random_numb = rand() % N;
        fwrite(&random_numb, sizeof(int), WRITE_COUNT, f);
    }
}

void print_menu()
{
    puts("Actions with app.exe: ");
    puts("Print file: app.exe p file_name");
    puts("Sort file: app.exe s file_name");
    puts("Create file: app.exe c file_name");
}

int main(const int argc, const char *const argv[])
{
    setbuf(stdout, NULL);
    FILE *f; 
    
    print_menu();
    if (argc != CORR_COUNT_ARGS)
    {
        puts("You enter invalid counts of arguments");
        return INVALID_COUNT_ARGS;
    }

    if (argv[TOKEN][0] == 'p')
    {
        f = fopen(argv[FILE_NAME], "rb");
        puts("Print file: ");
        const int count_numbs = print_file(f);
        if (0 == count_numbs)
        {
            return FILE_IS_EMPTY;
        }
        fclose(f);
        return OK;
    }
        
    if (argv[TOKEN][0] == 's')
    {
        f = fopen(argv[FILE_NAME], "r + b");
        const int count_numbs = numb_counter(f);
        if (0 == count_numbs)
        {
            return FILE_IS_EMPTY;
        }
        sort_file(f, count_numbs);
        puts("File sorted by ascending.");
        fclose(f);
        return OK;
    }

    if (argv[TOKEN][0] == 'c')
    {
        f = fopen(argv[FILE_NAME], "wb");
        create_file(f);
        fclose(f);
        puts("File with random numbers created.");
        return OK;
    }

    return INCORRECT_TOKEN;
}
