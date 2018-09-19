#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void sigusr(int signum)
{
	printf("got signal %d \n",signum);
	exit(0);
}

int main()
{
	signal(SIGUSR1,sigusr);
	pid_t pid = -1;
	pid=fork();
	if(pid==0)
	{
		printf("chid : %d\n",getpid());
		pid_t ppid =-1;
		pid_t cpid=getpid();
		ppid=getppid();
		kill(ppid,SIGUSR1);
		exit(0);
	}
	else
	{
		while(1){}
	}
}
