#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

void do_cat(int fd) {
    char buf[4096];
    ssize_t nread;
    while ((nread = read(fd, buf, sizeof(buf))) > 0) {
        write(1, buf, nread);
    }
}

int main(int argc, char **argv) {
    // With no arg
    if (argc == 1) {
        do_cat(STDIN_FILENO);
        exit(0);
    }

    // With args
    int fd;
    for (int i = 1; i < argc; i++) {
        if ((fd= open(argv[i], O_RDONLY)) == -1) {
            perror("open");
            exit(1);
        }
        do_cat(fd);
    }
    exit(0);
}
