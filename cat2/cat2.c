#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *fd;
  if (argc == 1) {
    fd = stdin;
  } else {
    fd = fopen(argv[1], "r");
  }

  int c;
  while((c = fgetc(fd)) != EOF) {
    fputc(c, stdout);
  }

  exit(0);
}
