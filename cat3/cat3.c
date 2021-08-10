#include <stdio.h>
#include <stdlib.h>


void die(const char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}


void put_or_die(int c, FILE* f)
{
    if (fputc(c, f) == EOF)
        die(NULL);
}


void cat_file(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        die(path);
    }

    int c;
    while ((c = fgetc(f)) != EOF)
    {
        switch (c)
        {
            case '\t':
                put_or_die('\\', stdout);
                put_or_die('t', stdout);
                continue;

            case '\n':
                put_or_die('$', stdout);
                put_or_die('\n', stdout);
                continue;

            default:
                put_or_die(c, stdout);
                continue;
        }
    }

    if (ferror(f) != 0)
    {
        die(path);
    }

    if (fclose(f) == EOF)
    {
        die(path);
    }
}


int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "No argument given\n");
    }

    for (int i = 1; i < argc; i++)
    {
        cat_file(argv[i]);
    }

    exit(EXIT_SUCCESS);
}
