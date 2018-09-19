#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid = -1;
	int i =0;
	for(i=0;i<10;i++)
	{
		pid=fork();
		if(pid==-1)
		{
			perror("fork failed");
			return 0;
		}
		else if(pid== 0)
		{
			printf("child process with pid %d\n",getpid());
			return 0;
		}
	}
	return 0;
}
