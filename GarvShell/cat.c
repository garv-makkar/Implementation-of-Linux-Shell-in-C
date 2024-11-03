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
#include <errno.h>
#include <signal.h>


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

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		while(1){
			char* a=read_command();
			printf("%s\n",a);
		}
	}
	else if(argc==2 && (strcmp(argv[1],"-n")==0 || strcmp(argv[1],"-E")==0))
	{
		printf("Invalid command\n");
	}
	else if (argc>2  && strcmp(argv[1],"-n")==0)
	{
		FILE *file;
		int chr;
		int count;
		int i;
		for (count = 2; count < argc; count++)
		{
			if ((file = fopen(argv[count], "r")) == NULL)
			{
				fprintf(stderr, "cat: %s : %s\n", argv[count], strerror(errno));
				continue;
			}
			else
			{
				i = 1;
				printf("    %d ", i);
				while ((chr = getc(file)) != EOF)
					if (chr == '\n')
					{
						fprintf(stdout, "%c", chr);
						i++;
						printf("    %d ", i);
					}
					else
					{
						fprintf(stdout, "%c", chr);
					}

				fclose(file);
			}
		}
	}
	else if (argc>2  && strcmp(argv[1],"-E")==0)
	{
		FILE *file;
		int chr;
		int count;

		for (count = 2; count < argc; count++)
		{
			if ((file = fopen(argv[count], "r")) == NULL)
			{
				fprintf(stderr, "cat: %s : %s\n", argv[count], strerror(errno));
				continue;
			}
			else
			{
				while ((chr = getc(file)) != EOF)
					if (chr == '\n')
					{
						printf("%c", '$');
						fprintf(stdout, "%c", chr);
					}
					else
					{
						fprintf(stdout, "%c", chr);
					}

				fclose(file);
			}
		}
	}
	else if (argc>=2)
	{
		FILE *file;
		int chr;
		int count;
		for (count = 1; count < argc; count++)
		{
			if ((file = fopen(argv[count], "r")) == NULL)
			{
				fprintf(stderr, "cat: %s : %s\n", argv[count], strerror(errno));
				continue;
			}
			else
			{
				while ((chr = getc(file)) != EOF)
					fprintf(stdout, "%c", chr);
				fclose(file);
			}
		}
	}
	return 0;
}
