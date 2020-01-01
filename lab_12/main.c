#include <stdio.h>
#include <string.h>

#include "list_operations.h"
#include "string_operations.h"
#include "struct.h"

#define MAX_ACTION_SIZE 4
#define MAX_BUFFER_SIZE 1600
#define READ_OK 1

#define OK 0
#define INPUT_ERROR 1
#define KEY_ERROR 2

int main(void)
{
    setbuf(stdout, NULL);

    char action[MAX_ACTION_SIZE];
    char first_buffer[MAX_BUFFER_SIZE] = { '\0' };
    char second_buffer[MAX_BUFFER_SIZE] = { '\0' };
    node_t *first_list_head, *second_list_head;
    int code_error;

    if ((code_error = get_line(stdin, MAX_ACTION_SIZE, action)))
    {
        return code_error;
    }

    if ((code_error = get_line(stdin, MAX_BUFFER_SIZE, first_buffer)))
    {
        return code_error;
    }

    if ((code_error = create_string_list(first_buffer, &first_list_head)))
    {
        return code_error;
    }

    switch (key_from_string(action))
    {
        case OUT_STRING:
            print_list(stdout, first_list_head->next_node);
            break;
        case DOUBLE_SPACES_DELETE:
            delete_double_spaces(first_list_head);
            print_list(stdout, first_list_head->next_node);
            break;
        case CONCAT_STRINGS:
            if ((code_error = get_line(stdin, MAX_BUFFER_SIZE, second_buffer)))
            {
                free_list(first_list_head);
                return code_error;
            }

            if ((code_error = create_string_list(second_buffer, &second_list_head)))
            {
                free_list(first_list_head);
                return code_error;
            }

            if ((code_error = concat_strings(first_list_head, second_list_head)))
            {
                free_list(first_list_head);
                free_list(second_list_head);
                return code_error;
            }

            print_list(stdout, first_list_head->next_node);
            free_list(second_list_head);
            break;
        case FIND_SUBSTRING:
            if ((code_error = get_line(stdin, MAX_BUFFER_SIZE, second_buffer)))
            {
                free_list(first_list_head);
                return code_error;
            }

            if ((code_error = create_string_list(second_buffer, &second_list_head)))
            {
                free_list(first_list_head);
                return code_error;
            }

            printf("%d\n", find_substring(first_list_head, second_list_head));
            free_list(second_list_head);
            break;
        default:
            free_list(first_list_head);
            return KEY_ERROR;
    }

    free_list(first_list_head);

    return OK;
}
