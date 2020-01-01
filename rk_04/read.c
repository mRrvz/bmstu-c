#include "read.h"
#include "list.h"

#define OK 0
#define READ_OK 1

void read_file(FILE *f, node_t **head)
{
    node_t *temp;
    char c;

    fscanf(f, "%c", &c);

    while (c != '\n')
    {
        temp = malloc(sizeof(node_t));
        (*head)->character = c;
        temp->next_node = *head;
        *head = temp;
        fscanf(f, "%c", &c);
    }

    temp = (*head)->next_node;
    free(*head);
    *head = temp;
}
