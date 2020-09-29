#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "expected one argument\n");
        exit(1);
    }

    DIR *dirp;
    if ((dirp = opendir(argv[1])) == NULL) {
        perror(argv[1]);
        exit(1);
    }

    struct dirent *ent;
    while ((ent = readdir(dirp)) != NULL)
        printf("%s\n", ent->d_name);

    closedir(dirp);
    exit(0);
}
