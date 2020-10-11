#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

static int open_connection(char *host, char *service) {
    struct addrinfo hints, *res, *ai;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(host, service, &hints, &res);
    if (err) {
        fprintf(stderr, "getaddrinfo(3): %s\n", gai_strerror(err));
        exit(1);
    }

    int sock;
    for (ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (sock < 0) continue;

        if (connect(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            close(sock);
            continue;
        }

        freeaddrinfo(res);
        return sock;
    }

    fprintf(stderr, "socket(2)/connect(2) failed\n");
    freeaddrinfo(res);
    exit(1);
}

int main(int argc, char **argv) {
    char *host = argc > 1 ? argv[1] : "localhost";
    int sock = open_connection(host, "daytime");

    FILE *f = fdopen(sock, "r");
    if (!f) {
        perror("fdopen(3)");
        exit(1);
    }

    char buf[4096];
    fgets(buf, sizeof(buf), f);
    fclose(f);

    printf("%s", buf);

    exit(0);
}
