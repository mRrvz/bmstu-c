#include <stdlib.h>
#include <string.h>

#include "list_operations.h"

#define PART_OF_LINE_SIZE 4
#define MAX_BUFFER_SIZE 1600

#define OK 0
#define MEMORY_ERROR 3

void print_list(FILE *f, const node_t *head)
{
    while (head != NULL)
    {
        for (int i = 0; i < PART_OF_LINE_SIZE; i++)
        {
            if (head->part_of_string[i] != '\0')
            {
                fprintf(f, "%c", head->part_of_string[i]);
            }
        }

        head = head->next_node;
    }

    putchar('\n');
}

void free_list(node_t *head)
{
    node_t *temp = head->next_node;
    free(head);

    while (temp != NULL)
    {
        head = temp;
        temp = head->next_node;

        free(head->part_of_string);
        free(head);
    }
}

static int create_part_of_string(node_t *const previous_node, const char *const string)
{
    node_t *current_node;
    char *part_of_string;

    if ((current_node = malloc(sizeof(node_t))) == NULL)
    {
        return MEMORY_ERROR;
    }

    if ((part_of_string = malloc(PART_OF_LINE_SIZE)) == NULL)
    {
        free(current_node);
        return MEMORY_ERROR;
    }

    strncpy(part_of_string, string, PART_OF_LINE_SIZE);

    current_node->part_of_string = part_of_string;
    current_node->next_node = NULL;
    previous_node->next_node = current_node;

    return OK;
}

int create_string_list(const char *string, node_t **head)
{
    int code_error;

    if ((*head = malloc(sizeof(node_t))) == NULL)
    {
        return MEMORY_ERROR;
    }

    node_t *temp_node = *head;

    do
    {
        if ((code_error = create_part_of_string(temp_node, string)))
        {
            free_list(*head);
            return code_error;
        }

        temp_node = temp_node->next_node;
    } while (*(string += PART_OF_LINE_SIZE));

    return OK;
}
