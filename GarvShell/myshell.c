#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>

// no.of Internal_commands
#define Internal_commands_ 4

char *copy[1024];

// implemented command names

char *Internal_commands[] = {"cd", "exit", "pwd", "echo"};
char *External_commands[] = {"ls", "mkdir", "cat", "date", "rm"};

// Environment variables
char current_working_directory[1024]; // current working directory

void print_cwd(char *cwd)
{
    printf("%s", cwd);
}

char *read_command()
{
    char *command_string;
    command_string = malloc(1000 * sizeof(char));
    fgets(command_string, 1000, stdin);
    if (command_string == NULL)
    {
        command_string = "Input error";
    }
    int i = 0;
    while (command_string[i] != '\n')
    {
        i++;
    }
    command_string[i] = '\0';
    return command_string;
}

char **split_command_string(char *command_string, char *splitwith)
{
    int position = 0;
    int no_of_tokens = 100;
    char **tokens = malloc(sizeof(char *) * no_of_tokens);

    // Split the command line into tokens with space as " "
    char *token = strtok(command_string, splitwith);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;
        token = strtok(NULL, splitwith);
    }
    // tokens[position-1][strlen(tokens[position-1])-1]='\0';
    tokens[position] = NULL;
    return tokens;
}

// cd

void run_cd(char **command)
{
    if (command[1] == NULL)
    {
        chdir("/home/garv/Desktop/Cprograms/GarvShell/");
    }
    else if (command[2] != NULL)
    {
        printf("Too many arguments\n");
    }
    else if (strcmp(command[1], "~") == 0)
    {
        chdir("/home/garv/Desktop/Cprograms/GarvShell");
    }
    else if (chdir(command[1]) == -1)
    {
        perror("");
        return;
    }
    getcwd(current_working_directory, sizeof(current_working_directory));
}

// exit

void run_exit(char **command_arr)
{
    exit(0);
}

// pwd

void run_pwd(char **command_arr)
{
    if (command_arr[1]==NULL){
       printf("%s\n",current_working_directory); 
    }
    else if(strcmp(command_arr[1],"-L")==0){
        printf("%s\n",current_working_directory);
    }
    else if(strcmp(command_arr[1],"-P")==0){
        printf("%s\n",current_working_directory);
    }
    else{
        printf("%s\n",current_working_directory);
    }
}

// echo

void run_echo(char **command_arr)
{

    if (command_arr[1] == NULL)
    {
        printf("\n");
        return;
    }
    if (strcmp(command_arr[1], "-n") == 0)
    {
        int i = 2;
        while (1)
        {
            if (command_arr[i] != NULL)
            {
                char c = '$';
                char *ptr = malloc(2 * sizeof(char));
                ptr[0] = c;
                ptr[1] = '\0';
                char d = command_arr[i][0];
                char *ptr2 = malloc(2 * sizeof(char));
                ptr2[0] = d;
                ptr2[1] = '\0';
                if (strcmp(ptr2, ptr) == 0)
                {
                    i++;
                }
                else
                {
                    printf("%s ", command_arr[i]);
                    i++;
                }
            }
            else
            {
                break;
            }
        }
    }
    else if (command_arr[1] != NULL)
    {
        int i = 1;
        while (1)
        {
            if (command_arr[i] != NULL)
            {
                char c = '$';
                char *ptr = malloc(2 * sizeof(char));
                ptr[0] = c;
                ptr[1] = '\0';
                char d = command_arr[i][0];
                char *ptr2 = malloc(2 * sizeof(char));
                ptr2[0] = d;
                ptr2[1] = '\0';
                if (strcmp(ptr2, ptr) == 0)
                {
                    i++;
                }
                else
                {
                    printf("%s ", command_arr[i]);
                    i++;
                }
            }
            else
            {
                break;
            }
        }
        printf("\n");
    }
}

void run_internal_commands(char **command)
{
    if (strcmp(command[0], "cd") == 0)
    {
        run_cd(command);
    }
    if (strcmp(command[0], "echo") == 0)
    {
        run_echo(command);
    }
    if (strcmp(command[0], "pwd") == 0)
    {
        run_pwd(command);
    }
    if (strcmp(command[0], "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
}

void change_process(pid_t pid, char **command_arr)
{
    pid = vfork();
    if (pid < 0)
    {
        printf("Fork failed...\n");
        return;
    }
    else if (pid == 0)
    {
        char cmd[1024];
        sprintf(cmd, "/home/garv/Desktop/Cprograms/GarvShell/%s", command_arr[0]);
        command_arr[0] = cmd;
        execvp(cmd, command_arr);
    }
    else
    {
        wait(NULL);
    }
}

void *change_process_2(void *arg)
{
    char *location = (char *)malloc(sizeof(char) * 100);
    strcpy(location, "/home/garv/Desktop/Cprograms/GarvShell/");
    int i = 0;
    while (copy[i] != NULL)
    {
        strcat(location, copy[i]);
        strcat(location, " ");
        i++;
    }
    int k = 0;
    while (location[k] == EOF)
    {
        k++;
    }
    location[k - 2] = '\0';
    system(location);
    return NULL;
}

void run_External_Commands_with_fork_exec(char **command_arr)
{
    pid_t pid;
    if (strcmp(command_arr[0], "ls") == 0 || strcmp(command_arr[0], "mkdir") == 0 || strcmp(command_arr[0], "rm") == 0 || strcmp(command_arr[0], "cat") == 0 || strcmp(command_arr[0], "date") == 0)
    {
        change_process(pid, command_arr);
    }
}

void run_external_commands_with_pthread(char **command_arr)
{

    if (strcmp(command_arr[0], "ls") == 0 || strcmp(command_arr[0], "mkdir") == 0 || strcmp(command_arr[0], "rm") == 0 || strcmp(command_arr[0], "cat") == 0 || strcmp(command_arr[0], "date") == 0)
    {
        pthread_t newthread;
        pthread_create(&newthread, NULL, &change_process_2, NULL);
        pthread_join(newthread, NULL);
    }
}

int is_pthread_command(char **command_arr)
{
    int i = 0;
    while (command_arr[i] != NULL)
    {
        i++;
    }
    int no_of_e = i;
    if (strcmp(command_arr[i - 1], "&t") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{

    getcwd(current_working_directory, sizeof(current_working_directory)); // Initialize current_working_directory Environment Variable

    // decleration of arrays,strings,ints etc...
    char *command_string;
    char **command_array;
    char *token;

    // infinte loop
    while (1)
    {
        print_cwd(current_working_directory);
        printf(":~ $ ");
        command_string = read_command();
        if (*command_string != '\0')
        {

            command_array = split_command_string(command_string, " ");

            int flag = 0;

            int i = 0;
            while (Internal_commands[i] != NULL)
            {
                if (strcmp(command_array[0], Internal_commands[i]) == 0)
                {
                    flag++;
                }
                i++;
            }
            i = 0;
            while (External_commands[i] != NULL)
            {
                if (strcmp(command_array[0], Internal_commands[i]) == 0)
                {
                    flag++;
                }
                i++;
            }
            if (flag > 0)
            {
                run_internal_commands(command_array);

                if (is_pthread_command(command_array) == 1)
                {
                    int i = 0;
                    while (command_array[i] != NULL)
                    {
                        i++;
                    }
                    command_array[i - 1] = NULL;
                    int k = 0;
                    while (command_array[k] != NULL)
                    {
                        copy[k] = command_array[k];
                        k++;
                    }
                    run_external_commands_with_pthread(command_array);
                }
                else
                {
                    run_External_Commands_with_fork_exec(command_array);
                }
            }
            else
            {
                printf("Invalid Command\n");
            }
        }
        else
        {
            continue;
        }
    }

    return 0;
}