#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define SIZE 100

char *executeCommand()
{
    char *MSGINPUT = "Enter a command:";
    char *cmd = (char *)malloc(SIZE * sizeof(char));
    if (cmd == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    if (write(STDOUT_FILENO, MSGINPUT, sizeof(MSGINPUT)) > -1)
    {
        fgets(cmd, SIZE, stdin);
    }

    // Remove the newline character from the end of the input
    size_t len = strlen(cmd);
    if (len > 0 && cmd[len - 1] == '\n')
    {
        cmd[len - 1] = '\0';
    }

    return cmd;
}

int main()
{
    char *MSG = "enseash%% %s\n";
    while (1)
    {
        char *command = executeCommand();
        // Do something with the command, e.g., execute it using system()
        printf(command);
        if (execl(command, "") == 0)
        {
            printf("\n");
        }
        else
        {
            perror("erreur you can't execute this command\n");
        }
        // Free the allocated memory
        free(command);
    }

    return 0;
}
