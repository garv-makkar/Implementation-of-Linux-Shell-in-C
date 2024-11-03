#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main(int argc, char **argv)
{

    char temp[100];
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);;
    struct tm *universal_time = gmtime(&t);

    strftime(temp, 100, "%A", local_time);

    if(t < 0)
    {
        printf("There is an error in showing time\n");
        return;
    }

    else
    {
        if (argc>=2 && strcmp(argv[1], "-u") != 0 && strcmp(argv[1], "-A") != 0){
            printf("Invalid input\n");
        }
        else if (argc==1)
        {
            printf("IST %s", asctime(local_time));
        }
        else if (argc == 2 && (strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "-A") == 0))
        {
            if (strcmp(argv[1], "-u") == 0)
            {
                printf("UTC %s", asctime(universal_time));
            }
            else if (strcmp(argv[1], "-A") == 0)
            {
                printf("%s\n", temp);
            }
        }
        else
        {
            printf("Invalid input\n");
        }
    }
}
