#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>

static void do_grep(regex_t *preg, FILE *src, int opt_invertmatch) {
    char buf[4096];
    int matched;
    while (fgets(buf, sizeof(buf), src) != NULL) {
        matched = (regexec(preg, buf, 0, NULL, 0) == 0);
        if (matched) {
            if (!opt_invertmatch) fputs(buf, stdout);
        } else {
            if (opt_invertmatch) fputs(buf, stdout);
        }
    }
}

int main(int argc, char **argv) {
    // options
    int opt_ignorecase = 0;
    int opt_invertmatch = 0;

    int opt;
    while ((opt = getopt(argc, argv, "iv")) != -1) {
        switch (opt) {
        case 'i':
            opt_ignorecase = 1;
            break;
        case 'v':
            opt_invertmatch = 1;
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
    if (opt_ignorecase) regmode = REG_ICASE;

    regex_t reg;
    if (regcomp(&reg, argv[0], regmode) != 0) {
        printf("recomp failed\n");
        exit(1);
    }

    if (argc == 1) {
        do_grep(&reg, stdin, opt_invertmatch);
    } else {
        FILE *f;
        if ((f = fopen(argv[1], "r")) == NULL) {
            perror(argv[1]);
            exit(1);
        }
        do_grep(&reg, f, opt_invertmatch);
        fclose(f);
    }

    regfree(&reg);
    exit(0);
}
