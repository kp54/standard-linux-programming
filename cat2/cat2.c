#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "No argument given\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++)
    {
        const char* path = argv[i];

        FILE* f = fopen(path, "r");
        if (f == NULL)
        {
            perror(path);
            exit(EXIT_FAILURE);
        }

        int c;
        while ((c = fgetc(f)) != EOF)
        {
            if (fputc(c, stdout) == EOF)
                break;
        }

        if (ferror(f) != 0)
        {
            // fgetc -> perror が正しいのか微妙
            // manにはerrnoセットするとは書いてない
            perror(path);
            exit(EXIT_FAILURE);
        }

        if (fclose(f) == EOF)
        {
            perror(path);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
