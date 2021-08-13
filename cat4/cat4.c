#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void die(char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}


void do_cat(char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        die(path);

    const int buffer_size = 4096;
    char *buf[buffer_size];
    while (true)
    {
        int n = fread(buf, sizeof(typeof(buf[0])), buffer_size, f);

        if (n < buffer_size && ferror(f) != 0)
        {
            die(path);
        }

        int wrote = 0;
        while (wrote < n)
        {
            wrote += fwrite(buf, sizeof(typeof(buf[0])), n, stdout);
            if (ferror(stdout) != 0)
                die("stdout");
        }

        if (feof(f) != 0)
            break;
    }

    if (fclose(f) == EOF)
        die(path);
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "No argument given\n");
    }

    for (int i = 1; i < argc; i++)
    {
        do_cat(argv[i]);
    }

    exit(EXIT_SUCCESS);
}
