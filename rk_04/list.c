#include "list.h"

node_t *create_list(void)
{
    node_t *head = malloc(sizeof(node_t));
    head->next_node = NULL;

    return head;
}

void print_list(FILE *f, const node_t *head)
{
    do
    {
        fprintf(f, "%c", head->character);
        head = head->next_node;
    } while (head != NULL);
}

void free_list(node_t *head)
{
    node_t *temp;
    do
    {
        temp = head->next_node;
        free(head);
        head = temp;
    } while ((temp = head) != NULL);
}
