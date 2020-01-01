#include <stdlib.h>
#include <string.h>

#include "string_operations.h"

#define PART_OF_LINE_SIZE 4

#define OK 0
#define INPUT_ERROR 1
#define MEMORY_ERROR 3
#define NO_SUBSTRING -1

#define READ_OK 1

static keys_table_t table[] =
{
    { "out", OUT_STRING },
    { "cat", CONCAT_STRINGS },
    { "sps", DOUBLE_SPACES_DELETE },
    { "pos", FIND_SUBSTRING }
};

#define KEYS_COUNT sizeof(table) / sizeof(keys_table_t)

int key_from_string(const char *const string)
{
    for (int i = 0; i < KEYS_COUNT; i++)
    {
        if (!strcmp(string, table[i].value))
        {
            return table[i].key;
        }
    }

    return BAD_KEY;
}

int concat_strings(node_t *first_list_head, node_t *second_list_head)
{
    node_t *tail = first_list_head;
    while (tail->next_node != NULL)
    {
        tail = tail->next_node;
    }

    char *part_of_string;
    node_t *first_current_node;
    node_t *second_current_node = second_list_head->next_node;

    while (second_current_node != NULL)
    {
        if ((first_current_node = malloc(sizeof(node_t))) == NULL)
        {
            return MEMORY_ERROR;
        }

        if ((part_of_string = malloc(PART_OF_LINE_SIZE)) == NULL)
        {
            free(first_current_node);
            return MEMORY_ERROR;
        }

        strncpy(part_of_string, second_current_node->part_of_string, PART_OF_LINE_SIZE);

        first_current_node->part_of_string = part_of_string;
        first_current_node->next_node = NULL;
        tail->next_node = first_current_node;
        tail = tail->next_node;
        second_current_node = second_current_node->next_node;
    }

    return OK;
}

static void shift_string(node_t *node, const int start, const int size)
{
    for (int i = start; i < size - 1; i++)
    {
        node->part_of_string[i] = node->part_of_string[i + 1];
    }

    node->part_of_string[size - 1] = '\0';
}

int shift_needed(int i, node_t *node, bool is_last_space)
{
    return node->part_of_string[i] == ' ' && (node->part_of_string[i + 1] == ' ' || (is_last_space && i == 0));
}

void delete_double_spaces(node_t *list_head)
{
    node_t *current_node = list_head->next_node;
    bool is_last_space = false;

    for (int size; current_node != NULL; size = PART_OF_LINE_SIZE, current_node = current_node->next_node)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (shift_needed(i, current_node, is_last_space))
            {
                shift_string(current_node, i, size);
                i--;
                size--;
            }
        }

        if (is_last_space && !(size - 1) && current_node->part_of_string[size - 1] == ' ')
        {
            current_node->part_of_string[size - 1] = '\0';
            is_last_space = true;
        }
        else
        {
            is_last_space = current_node->part_of_string[size - 1] == ' ';
        }
    }
}

int find_substring(node_t *first_list_head, node_t *second_list_head)
{
    int substring_index = 0, current_index = 0, k = 0;
    node_t *current_first_node = first_list_head->next_node;
    node_t *current_second_node = second_list_head->next_node;

    while (current_first_node != NULL)
    {
        for (int i = 0; i < PART_OF_LINE_SIZE; i++, current_index++)
        {
            if (current_first_node->part_of_string[i] == current_second_node->part_of_string[k])
            {
                if (k == 0 && current_second_node == second_list_head->next_node)
                {
                    substring_index = current_index;
                }

                if (++k == PART_OF_LINE_SIZE)
                {
                    if (current_second_node->next_node == NULL)
                    {
                        return substring_index;
                    }
                    else
                    {
                        current_second_node = current_second_node->next_node;
                        k = 0;
                    }
                }

                if (current_second_node->part_of_string[k] == '\0')
                {
                    return substring_index;
                }
            }
            else if (k != 0)
            {
                k = 0;
                current_second_node = second_list_head->next_node;
            }
        }

        current_first_node = current_first_node->next_node;
    }

    return NO_SUBSTRING;
}

int get_line(FILE *f, int maxsize, char *string)
{
    do
    {
        if ((fscanf(f, "%c", string)) != READ_OK)
        {
            return INPUT_ERROR;
        }
    } while ((*string++) != '\n' && --maxsize);
    *(string - 1) = '\0';

    return OK;
}
