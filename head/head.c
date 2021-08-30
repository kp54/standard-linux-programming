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
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    do_head(stdin, atol(argv[1]));

    exit(EXIT_SUCCESS);
}
