#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>


#define TOK_BUFSIZE 64


int main(int argc, char** argv)
{
	int bufferSize= TOK_BUFSIZE;
	char line[80];
	char* token;
	char* arguList[80]= {NULL};
	int i = 0;
	char* st_p;
	char instpath[80]= {NULL};
	struct stat buf;	
	char* env[]= {NULL};
	char* dir;	

	pid_t pid;

	//get current path
	const char *path = getenv("PATH");

	printf("Shell program starts here -> \n");	

	while(1)
	{
		fgets(line, 80, stdin);	
		line[strlen(line)-1] = '\0';
	

		//for quit command
		if(!strcmp(line, "quit"))
		{
			perror("End of Shell.\n");
			return 0;
		}
		
		pid = fork();


		token = strtok_r(line, " ", &st_p);
		memset(arguList, 0 , sizeof(arguList));


		for(i = 0; token; i++)
		{
			arguList[i] = token;
			token = strtok_r(NULL, " ", &st_p);
		}


		if(pid < 0)
		{
			perror("Fork error\n");
			return 0;
		}
		//parent process
		else if(pid)
		{
			pid = wait(0);
		}
		//child process, execute
		else
		{
			dir = strtok_r(path, ":", &st_p);
			if(!dir)
			{
				perror("Path error. \n");
				return 0;
			}


			memset(instpath, 0, sizeof(instpath));
			sprintf(instpath, "%s/%s", dir, arguList[0]);
		
			while(1)
			{
				if(stat(instpath, &buf)== 0)
				{
					execve(instpath, arguList, env);
					break;
				}
				else
				{
					dir = strtok_r(NULL, ":", &st_p);
					sprintf(instpath, "%s/%s", dir, arguList[0]);		

                    if(dir == NULL)
                    {
                        perror("No such command. \n");
                        break;
                    }
                }
            }
			exit(0);
        }
    }

	return 0;
}
	
