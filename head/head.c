#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "at least one argument expected\n");
        exit(1);
    }

    FILE *f;
    if (argc == 3) {
        if ((f = fopen(argv[2], "r")) == NULL) {
            perror("fopen");
            exit(1);
        }
    } else {
        f = stdin;
    }

    int nlines = atoi(argv[1]);
    int c;
    while ((c = getc(f)) != EOF) {
        putc(c, stdout);
        if (c == '\n') {
            nlines--;
            if (nlines == 0) break;
        }
    }

    exit(0);
}
