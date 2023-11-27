#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <linux/time.h>

#define MAX_INPUT_SIZE 1024

void printPrompt(int exitCode, long elapsedTime) {
    if (WIFEXITED(exitCode)) {
        printf("enseash [exit:%d|%ldms] %% ", WEXITSTATUS(exitCode), elapsedTime);
    } else if (WIFSIGNALED(exitCode)) {
        printf("enseash [sign:%d|%ldms] %% ", WTERMSIG(exitCode), elapsedTime);
    } else {
        printf("enseash [unknown|%ldms] %% ", elapsedTime);
    }
}

int main() {
    char user_input[MAX_INPUT_SIZE];

    while (1) {
        printf("enseash %% ");
        fgets(user_input, sizeof(user_input), stdin);

        // Remove the newline character at the end
        size_t len = strlen(user_input);
        if (len > 0 && user_input[len - 1] == '\n') {
            user_input[len - 1] = '\0';
        }

        if (strcmp(user_input, "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            struct timespec start, end;

            clock_gettime(CLOCK_MONOTONIC, &start);

            // Execute the command
            execlp(user_input, user_input, (char *)NULL);

            // If execlp fails
            perror("Error executing command");
            exit(EXIT_FAILURE);
        } else { // Parent process
            int status;
            struct timespec start, end;

            clock_gettime(CLOCK_MONOTONIC, &start);

            waitpid(pid, &status, 0);

            clock_gettime(CLOCK_MONOTONIC, &end);

            long elapsedTime = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

            printPrompt(status, elapsedTime);
        }
    }

    printf("Exiting the REPL. Goodbye!\n");

    return 0;
}
