#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define SIZE 100

char *executeCommand()
{
    char *cmd = (char *)malloc(SIZE * sizeof(char));
    
    //verify if there enough memory
    if (cmd == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter a command: ");
    if (fgets(cmd, SIZE, stdin) == NULL)
    {
        free(cmd);
        exit(EXIT_SUCCESS); // Exit if Ctrl+D is pressed
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
    while (1)
    {
        char *command = executeCommand();
        // Do something with the command, e.g., execute it using system()
        printf("enseash%% %s\n", command);
        if (strcmp(command, "exit") == 0 || strcmp(command, "<ctrl>+d") == 0)
        {
            printf("Bye bye...\n");
            system("exit");
            free(command);
            break;
        }
        printf("///\n");
        if (system(command) == 0)
        {
            printf("\n");
        }
        else
        {
            perror("Error: Unable to execute the command\n");
        }

        // Free the allocated memory
        free(command);
    }

    return 0;
}
