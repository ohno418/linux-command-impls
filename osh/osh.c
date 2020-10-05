#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

struct cmd {
    int argc;
    char **argv;
};

static char *read_arg_string(char *p) {
    char *endp = p;
    while (*endp != '\0' && *endp != '\n' && !isspace(*endp))
        endp++;
    int len = endp - p + 1; // including '\0'

    char *str = malloc(len);
    for (int i = 0; i < len - 1; i++) {
        str[i] = *p;
        p++;
    }
    str[len + 1] = '\0';
    return str;
}

static struct cmd *parse_cmd(char *str) {
    struct cmd *cmd = calloc(1, sizeof(struct cmd));
    cmd->argc = 0;
    cmd->argv = calloc(1, sizeof(char*) * 16);

    char *p = str;
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        cmd->argv[cmd->argc] = read_arg_string(p);
        p += strlen(cmd->argv[cmd->argc]);
        cmd->argc++;
    }

    return cmd;
}

static void cmd_loop(void) {
    for (;;) {
        printf("osh>> ");

        char buf[4096];
        fgets(buf, sizeof(buf), stdin);

        pid_t pid = fork();
        if (pid == -1) {
            // fork error
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // child process
            struct cmd *cmd = parse_cmd(buf);
            execv(cmd->argv[0], cmd->argv);
            // error
            perror(cmd->argv[0]);
            exit(1);
        } else {
            // parent process
            waitpid(pid, NULL, 0);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 1) {
        fprintf(stderr, "expected no argument\n");
        exit(1);
    }

    cmd_loop();
    exit(0);
}
