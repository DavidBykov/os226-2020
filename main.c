#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int rc;

int echo(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
    }
    return argc - 1;
}

int retcode(int argc, char* argv[])
{
    printf("%d\n", rc);
    return 0;
}

int main(int argc, char* argv[])
{
    rc = 0;
    char input[10000];
    char* saveptr1, * saveptr2;

    while (fgets(input, sizeof(input), stdin))
    {
        char* line = strtok_r(input, "\n;", &saveptr1);

        argc = 0;

        while (line != NULL)
        {
            char* ptr = strtok_r(line, " ", &saveptr2);

            while (ptr != NULL)
            {
                argv[argc++] = ptr;
                ptr = strtok_r(NULL, " ", &saveptr2);
            }

            if (strcmp(argv[0], "echo") == 0)
                rc = echo(argc, argv);

            if (strcmp(argv[0], "retcode") == 0)
                rc = retcode(argc, argv);

            line = strtok_r(NULL, "\n;", &saveptr1);
        }
    }

    return 0;
}