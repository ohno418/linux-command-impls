#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "one number expected\n");
        exit(1);
    }

    int nlines = atoi(argv[1]);

    int c;
    while ((c = getc(stdin)) != EOF) {
        putchar(c);
        if (c == '\n') {
            nlines--;
            if (nlines == 0) break;
        }
    }
    exit(0);
}
