#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>

int isDirectoryEmpty(char *dirname)
{
    int n = 0;
    struct dirent *d;
    DIR *dir = opendir(dirname);
    if (dir == NULL) // Not a directory or doesn't exist
        return 1;
    while ((d = readdir(dir)) != NULL)
    {
        if (++n > 2)
            break;
    }
    closedir(dir);
    if (n <= 2) // Directory Empty
        return 1;
    else
        return 0;
}

int isDir(const char* fileName)
{
    struct stat path;

    stat(fileName, &path);

    return S_ISREG(path.st_mode);
}

char *read_command()
{
    char *cmd_string;
    cmd_string = malloc(1000 * sizeof(char));
    fgets(cmd_string, 1000, stdin);
    if(cmd_string == NULL)
    {
        cmd_string = "Input error";
    }
    int i=0;
    while(cmd_string[i]!='\n'){
        i++;
    }
    cmd_string[i]='\0';
    return cmd_string;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("more argument(s) needed\n");
    }
    else if(argc>=3 && strcmp(argv[1],"-d")==0){
        for (int i = 2; i < argc; i++)
        {
            if (isDirectoryEmpty(argv[i]) == 1)
            {
                if (rmdir(argv[i]) < 0)
                {
                    perror(argv[i]);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("%s: directory is not empty\n",argv[i]);
            }
        }
        
    }
    else if(argc>=3 && strcmp(argv[1],"-i")==0){

        for (int i = 2; i < argc; i++)
        {
            printf("rm: remove file '%s'? ",argv[i]);
            char *ans =read_command();
            char c = 'y';
            char *ptr = malloc(2 * sizeof(char));
            ptr[0] = c;
            ptr[1] = '\0';
            char d = 'Y';
            char *ptr2 = malloc(2 * sizeof(char));
            ptr2[0] = d;
            ptr2[1] = '\0';

            if ((strcmp(ans,ptr)==0) || (strcmp(ans,ptr2)==0))
            {
                int file;
                file = open(argv[i], O_RDONLY);
                if (isDir(argv[i]) == 0)
                {
                    printf("rm: cannot remove '%s': It is either a directory or it does not exist\n", argv[i]);
                }
                else
                {
                    if (file != -1)
                    {
                        close(file);
                        remove(argv[i]);
                    }
                    else
                    {
                        perror(argv[i]);
                    }
                }
            }
        }
        
    }
    else if(argc >=2){
        for (int i = 1; i < argc; i++)
        {
            int file;
            file = open(argv[i], O_RDONLY);
            if(isDir(argv[i])==0){
                printf("rm: cannot remove '%s': It is either a directory or it does not exist\n", argv[i]);
            }
            else
            {
                if (file != -1)
                {
                    close(file);
                    remove(argv[i]);
                }
                else
                {
                    perror(argv[i]);
                }
            }
        }
    }
    
}