#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        struct dirent *entity;
        DIR *dir = opendir(".");
        if (dir != NULL)
        {
            entity = readdir(dir);
            while (entity != NULL)
            {
                if(strcmp(entity->d_name,".")==0 || strcmp(entity->d_name,"..")==0){
                    entity = readdir(dir);
                }
                else{
                    printf("%s ", entity->d_name);
                    entity = readdir(dir);
                }
            }
            printf("\n");
        }
        closedir(dir);
    }
    else if (argc==2 && (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "-1") == 0))
    {
        if (strcmp(argv[1], "-m") == 0)
        {
            struct dirent *entity;
            DIR *dir = opendir(".");
            if (dir != NULL)
            {
                entity = readdir(dir);
                while (entity != NULL)
                {
                    if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0)
                    {
                        entity = readdir(dir);
                    }
                    else
                    {
                        printf("%s, ", entity->d_name);
                        entity = readdir(dir);
                    }
                }
            }
            closedir(dir);
        }
        else if(strcmp(argv[1], "-1")==0)
        {
            struct dirent *entity;
            DIR *dir = opendir(".");
            if (dir != NULL)
            {
                entity = readdir(dir);
                while (entity != NULL)
                {
                    if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0)
                    {
                        entity = readdir(dir);
                    }
                    else
                    {
                        printf("%s\n", entity->d_name);
                        entity = readdir(dir);
                    }
                }
            }
            closedir(dir);
        }
    }
    else if (argc>2){
        printf("Invalid Command\n");
    }
    else{
        printf("Invalid Command\n");
    }
    return 0;
}