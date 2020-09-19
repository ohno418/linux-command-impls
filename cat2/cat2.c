#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

void do_cat(FILE *f) {
    int c;
    while((c = fgetc(f)) != EOF) {
        if (fputc(c, stdout) == EOF) {
            exit(1);
            perror("fputc");
        }
    }
}

int main(int argc, char **argv) {
    // With no arg
    if (argc == 1) {
        do_cat(stdin);
        exit(0);
    }

    // With args
    FILE *f;
    for (int i = 1; i < argc; i++) {
        if ((f = fopen(argv[i], "r")) == NULL) {
            perror("fopen");
            exit(1);
        }

        do_cat(f);
        fclose(f);
    }
    exit(0);
}
