#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

static void
die(const char *s)
{
    perror(s);
    exit(1);
}

#define BUFFER_SIZE 2048

static void
do_cat(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];

    fd = open(path, O_RDONLY);
    if (fd == -1) die(path);

    for (;;) {
        int n = read(fd, buf, sizeof buf);
        if (n == -1) die(path);
        if (n == 0) break;
        if (write(STDOUT_FILENO, buf, n) == -1) die(path);
    }

    if (close(fd) == -1) die(path);
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
    }

    for (int i=1; i<argc; i++) {
        do_cat(argv[i]);
    }

    exit(0);
}
