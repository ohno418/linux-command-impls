#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int nlines = 10;
    int opt;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch(opt) {
        case 'n':
            nlines = atoi(optarg);
            break;
        case '?':
        default:
            exit(1);
        }
    }

    FILE *f;
    if (argc == optind) {
        f = stdin;
    } else {
        if ((f = fopen(argv[optind], "r")) == NULL) {
            perror("fopen");
            exit(1);
        }
    }

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
