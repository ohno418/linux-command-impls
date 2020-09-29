#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "expected arguments\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        if (mkdir(argv[i], 0777) == -1) {
            perror(argv[i]);
            exit(1);
        }
    }

    exit(0);
}
