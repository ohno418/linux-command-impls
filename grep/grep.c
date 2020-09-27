#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>

static void do_grep(regex_t *preg, FILE *src) {
    char buf[4096];
    while (fgets(buf, sizeof(buf), src) != NULL) {
        if ((regexec(preg, buf, 0, NULL, 0)) == 0) {
            fputs(buf, stdout);
        }
    }
}

int main(int argc, char **argv) {
    // ignore case option (-i)
    int isIgnoreCase = 0;

    int opt;
    while ((opt = getopt(argc, argv, "i")) != -1) {
        switch (opt) {
        case 'i':
            isIgnoreCase = 1;
            break;
        case '?':
        default:
            exit(1);
        }
    }
    argc -= optind;
    argv += optind;

    if (argc < 1) {
        printf("expected at least 1 argument\n");
        exit(1);
    }

    int regmode = REG_EXTENDED;
    if (isIgnoreCase) regmode = REG_ICASE;

    regex_t reg;
    if (regcomp(&reg, argv[0], regmode) != 0) {
        printf("recomp failed\n");
        exit(1);
    }

    if (argc == 1) {
        do_grep(&reg, stdin);
    } else {
        FILE *f;
        if ((f = fopen(argv[1], "r")) == NULL) {
            perror(argv[1]);
            exit(1);
        }
        do_grep(&reg, f);
        fclose(f);
    }

    regfree(&reg);
    exit(0);
}
