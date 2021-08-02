#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>


void die(const char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}


int cat_fd (int fd)
{
    unsigned char buf[1024];
    while (true)
    {
        ssize_t n = read(fd, buf, sizeof buf);
        if (n < 0)
            return -1;
        if (n == 0)
            return 0;

        if (write(STDOUT_FILENO, buf, n) < 0)
            return -1;
    }
}


void cat_file (const char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);

    if (cat_fd(fd) < 0)
        die(path);

    if (close(fd) < 0)
        die(path);
}


void cat_stdin()
{
    if (cat_fd(STDIN_FILENO) < 0)
        die("stdin");
}


int main (int argc, char *argv[])
{
    if (argc < 2) {
        cat_stdin();
        exit(EXIT_SUCCESS);
    }

    for (int i = 1; i < argc; i++)
    {
        cat_file(argv[i]);
    }

    exit(EXIT_SUCCESS);
}
