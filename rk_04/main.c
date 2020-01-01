#include <stdio.h>
#include "list.h"
#include "read.h"

#define OUTFILE "out.txt"

#define OK 0
#define FILE_ERROR 1
#define ARGS_ERROR 2

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    FILE *f;

    if (argc < 1)
    {
        fprintf(stderr, "Invalid arguments!\n");
        return ARGS_ERROR;
    }

    if ((f = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Error while open file\n");
        return FILE_ERROR;
    }

    node_t *head = create_list();
    read_file(f, &head);
    fclose(f);

    if ((f = fopen(OUTFILE, "w")) == NULL)
    {
        fprintf(stderr, "Error while open file\n");
        return FILE_ERROR;
    }

    print_list(f, head);
    free_list(head);
    fclose(f);

    return OK;
}
