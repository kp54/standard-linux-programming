#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


static void do_head(FILE *f, long nlines)
{
    if (nlines <= 0)
        return;

    int c;
    while (true)
    {
        c = getc(f);
        if (c == EOF)
            return;

        if (putchar(c) < 0)
            exit(EXIT_FAILURE);

        if (c == '\n')
        {
            nlines--;

            if (nlines == 0)
                return;
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    long nlines = atol(argv[1]);

    if (argc == 2)
    {
        do_head(stdin, nlines);
        exit(EXIT_SUCCESS);
    }

    for (int i = 2; i < argc; i++)
    {
        char *path = argv[i];

        FILE* fp = fopen(path, "r");
        if (fp == NULL)
        {
            perror(path);
            exit(EXIT_FAILURE);
        }

        do_head(fp, nlines);

        if (fclose(fp) == EOF)
        {
            perror(path);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
