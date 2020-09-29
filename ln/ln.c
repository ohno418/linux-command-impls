#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "expected 2 arguments\n");
        exit(1);
    }

    if (link(argv[1], argv[2]) == -1) {
        perror("link");
        exit(1);
    }

    exit(0);
}
