#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void die(const char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}


void put_or_die(const char c, FILE *f)
{
    if (fputc(c, f) == EOF)
        die(NULL);
}


void put_char(const char c, FILE *f)
{
    if (c == '\t')
    {
        put_or_die('\\', f);
        put_or_die('t', f);
        return;
    }

    if (c == '\n')
    {
        put_or_die('$', f);
        put_or_die('\n', f);
        return;
    }

    put_or_die(c, f);
}


void cat_file(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        die(path);

    while (true)
    {
        char c = fgetc(f);
        if (c == EOF)
        {
            break;
        }

        put_char(c, stdout);
    }

    if (ferror(f) != 0)
        die(path);

    if (fclose(f) == EOF)
        die(path);
}


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "No argument given.");
    }

    for (int i = 1; i < argc; i++)
    {
        cat_file(argv[i]);
    }

    exit(EXIT_SUCCESS);
}
