//
// Created by mtwo on 26/05/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd)) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) { // Child process
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);

        execvp(argv[1], &argv[1]);
        perror("exec failed");
        exit(1);
    }

    close(pipefd[1]);
    char output[BUFFER_SIZE];
    ssize_t bytes = read(pipefd[0], output, BUFFER_SIZE - 1);
    output[bytes] = '\0';
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

    if (exit_code != 0 && strstr(output, "permission denied")) {
        printf("%s\n", output);
        printf("Re-run as root? [y/N] ");

        // Get single character input
        char answer = getchar();
        if (answer == 'y' || answer == 'Y') {
            // Build sudo command
            char **sudo_argv = malloc((argc + 1) * sizeof(char *));
            sudo_argv[0] = "sudo";
            for (int i = 1; i < argc; i++) {
                sudo_argv[i] = argv[i];
            }
            sudo_argv[argc] = NULL;

            execvp("sudo", sudo_argv);
            perror("sudo failed");
            free(sudo_argv);
            return 1;
        }
    } else if (exit_code != 0) {
        printf("Command failed (exit %d)\n", exit_code);
    }

    return exit_code;
}
