#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void die(char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "No argument given\n");
        die(NULL);
    }

    char *path = argv[1];

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        die(path);
    }

    bool lf = false;
    int lines = 0;
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        lf = c == '\n';
        if (lf)
            lines++;
    }

    if (fclose(file) == EOF)
    {
        die(path);
    }

    if (!lf) {
        lines++;
    }

    printf("%s: %d\n", path, lines);

    exit(EXIT_SUCCESS);
}
