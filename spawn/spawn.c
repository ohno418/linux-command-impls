#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "expected 2 arguments\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // child process
        execl(argv[1], argv[1], argv[2], NULL);
        perror(argv[1]);
        exit(99);
    } else {
        // parent process
        int status;
        waitpid(pid, &status, 0);
        printf("child (PID=%d) finished; ", pid);

        if (WIFEXITED(status))
            printf("exit, status=%d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("signal, sig=%d\n", WTERMSIG(status));
        else
            printf("abnormal exit\n");
        exit(0);
    }
}
