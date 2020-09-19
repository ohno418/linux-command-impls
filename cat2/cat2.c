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

void do_cat_with_path(char *path) {
    FILE *f;
    if ((f = fopen(path, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    do_cat(f);
    fclose(f);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        do_cat(stdin);
    } else {
        for (int i = 1; i < argc; i++) {
            do_cat_with_path(argv[i]);
        }
    }

    exit(0);
}
