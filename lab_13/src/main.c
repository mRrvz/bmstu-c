#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include "../include/dirname.h"

#define OK 0
#define OPEN_ERROR 1
#define DL_ERROR 2
#define ARGS_ERROR 3

#define STD_ARGS_COUNT 2

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        return ARGS_ERROR;
    }

    if (!strcmp(argv[1], "dlopen"))
    {
        int (*dirname)(int, char **);
        char *error;

        void *dirname_lib = dlopen("libdirname.so", RTLD_LAZY);
        if (dirname_lib == NULL)
        {
            fprintf(stderr, "dlopen error: %s\n", dlerror());
            return OPEN_ERROR;
        }

        dirname = dlsym(dirname_lib, "dirname");
        if ((error = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", error);
            return DL_ERROR;
        }

        int code_error = (*dirname)(argc - STD_ARGS_COUNT, argv + STD_ARGS_COUNT);
        dlclose(dirname_lib);

        return code_error;
    }

    return dirname(argc - STD_ARGS_COUNT, argv + STD_ARGS_COUNT);
}
