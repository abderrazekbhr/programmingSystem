#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#define SIZE 100

char *executeCommand()
{
    const char *MSGINPUT = "enseash%% ";

    char *cmd = (char *)malloc(SIZE * sizeof(char));
    if (cmd == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    if (write(STDOUT_FILENO, MSGINPUT, strlen(MSGINPUT)) == -1)
    {
        perror("Error writing to the terminal");
        free(cmd);
        exit(EXIT_FAILURE);
    }

    ssize_t bytesRead = read(STDIN_FILENO, cmd, SIZE);
    if (bytesRead == -1)
    {
        perror("Error reading from the terminal");
        free(cmd);
        exit(EXIT_FAILURE);
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
    const char *ERRORMSG = "Erreur: You can't execute this command\n";
    char *command;
    clock_t t_init_child; //for getting the time when the child is initialized
    clock_t t_finish_child; //for getting the time when the child is finshed
    
    while (1)
    {

        command = executeCommand();
        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
       
        t_init_child = clock(); //get time start child
        // child process
        if (child_pid == 0)
        {
            sleep(2);
            printf("pid_fils=%d\n", getpid());
            // Exit the loop if the command is "exit" or if Ctrl+D (EOF) is reached

            if (strcmp(command, "exit") == 0 || strlen(command) == 0)
            {
                write(STDOUT_FILENO, "Bye bye...\n", strlen("Bye bye...\n"));
                free(command);
                break;
            }
            if (execlp(command, command, NULL) == -1)
            {
                perror(ERRORMSG);
                free(command);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }

        // parent instruction
        else
        {
            int status;
            wait(&status);
            t_finish_child = clock();//get finsh time for child

            double finish = (t_finish_child - t_init_child)/ (CLOCKS_PER_SEC / 1000000.0);    // Calculate the elapsed time in milliseconds
 
            char msgState[100] = "\0";

            // test if the process complete correcty or if there is an interruption and specify which type of interruption presented
            if (WIFEXITED(status))
            {
                sprintf(msgState, "enseash %% [exit : %d | %dms]\n\0", WEXITSTATUS(status), (long) finish);
                write(STDOUT_FILENO, msgState, sizeof(msgState));
            }
            else
            {
                sprintf(msgState, "enseash %% [sign : %d | %dms]\n\0", status, (long)finish);
                write(STDOUT_FILENO, msgState, sizeof(msgState));
            }
            command = "\0";
            // free memory
        }
    }
}