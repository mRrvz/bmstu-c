/* dirname -- strip suffix from file name
   super function by Romanov Alexey
*/

#include <stdio.h>
#include <string.h>
#include "../include/dirname.h"

#define OK 0
#define INVALID_ARG 1

#define FORMAT_SIZE 4

static char *__dirname(char *path)
{
    int i;

    if (path == NULL || path[0] == '\0')
    	return ".";

    for (i = strlen(path) - 1; i >= 0 && path[i] == '/'; i--);

    if (i == -1)
    	return "/";

    for (i--; i >= 0 && path[i] != '/'; i--);

    if (i == -1)
    	return ".";

    path[i] = '\0';

    for (i--; i >= 0 && path[i] == '/'; i--);

    if (i == -1)
    	return "/";

    path[i + 1] = '\0';

    return path;
}

static void usage(void)
{
    fprintf(stderr, "Please, send path to function\n");
}

int dirname(int argc, char *argv[])
{
    char format[FORMAT_SIZE] = "%s\n";

    if (argv == NULL)
    {
        usage();
        return INVALID_ARG;
    }

    if (!strcmp(argv[argc - 1], "-z") || !strcmp(argv[argc - 1], "--zero"))
    {
    	format[FORMAT_SIZE - 2] = '\0';
    	argc--;
    }

    for (int i = 0; i < argc; i++)
    {
    	fprintf(stdout, format, __dirname(argv[i]));
    }

    return OK;
}
