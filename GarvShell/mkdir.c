#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char **argv)
{

	if (argc == 1)
	{
		printf("mkdir: More argument(s) required\n");
	}
	else if (argc > 1)
	{
		if (argc == 2 && ((strcmp(argv[1], "-v") == 0)))
		{
			printf("Invalid command\n");
		}
		else if (argc > 2 && (strcmp(argv[1], "-v") == 0))
		{
			int k=0;
			for (int i = 2; i < argc; i++)
			{
				if (mkdir(argv[i], 0777) < 0)
				{					
					perror(argv[i]);	
				}
				else{
					printf("mkdir: %s created\n",argv[i]);
				}
			}
		}
		else{
			for (int i = 1; i < argc; i++)
			{
				if (mkdir(argv[i], 0777) < 0)
				{
					perror(argv[i]);
					
				}

			}

		}

	}


	return 0;
}
