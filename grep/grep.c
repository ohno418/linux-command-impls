#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void do_grep(regex_t *preg, FILE *src) {
    char buf[4096];
    while (fgets(buf, sizeof(buf), src) != NULL) {
        if ((regexec(preg, buf, 0, NULL, 0)) == 0) {
            fputs(buf, stdout);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("expected 2 arguments\n");
        exit(1);
    }

    regex_t reg;
    if (regcomp(&reg, argv[1], REG_EXTENDED) != 0) {
        printf("recomp failed\n");
        exit(1);
    }

    if (argc == 2) {
        do_grep(&reg, stdin);
    } else {
        FILE *f;
        if ((f = fopen(argv[2], "r")) == NULL) {
            perror("fopen");
            exit(1);
        }
        do_grep(&reg, f);
        fclose(f);
    }

    regfree(&reg);
    exit(0);
}
