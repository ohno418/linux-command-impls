#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd;
    if (argc == 1) {
        fd = 0;
    } else {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
    }

    char buf[4096];
    ssize_t nread;
    while ((nread = read(fd, buf, sizeof(buf))) > 0)
        write(1, buf, nread);

    return 0;
}
