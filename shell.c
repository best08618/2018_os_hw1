#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>

void main(int argc, char *argv[])
{
	pid_t cpid;
	

	while(1)
	{
		cpid = fork();
		if(cpid == 0)
		{
			execve();
			exit(0);
		}
		else if(cpid < 0)
		{
			printf("Child Process Error!\n");
		}
		else if(cpid > 0)
		{
			wait(0);
		}
	}

	return;
}
