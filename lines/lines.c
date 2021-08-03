#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>


void die(char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}


int count_lines(char *path)
{
    int fp = open(path, O_RDONLY);
    if (fp < 0)
        die(path);

    unsigned char buf[1024];
    int lines = 0;
    while (true)
    {
        int n = read(fp, buf, sizeof buf);
        if (n < 0)
            die(path);
        if (n == 0)
            break;

        for (int i = 0; i < n; i++)
        {
            if (buf[i] == '\n')
                lines++;
        }
    }

    return lines;
}


int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "no argument given\n");
        exit(EXIT_FAILURE);
    }

    int total = 0;
    for (int i = 1; i < argc; i++)
    {
        int l = count_lines(argv[i]);
        total += l;
        printf("%s: %d\n", argv[i], l);
    }

    if (2 < argc) {
        printf("total: %d\n", total);
    }

    exit(EXIT_SUCCESS);
}
