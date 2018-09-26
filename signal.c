#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

void sig_usr(int signum)
{
	printf("Got Signal: %d\n", signum);
	exit(0);
}

void main (int argc, char *argv[])
{
	pid_t cpid;
	signal(SIGUSR1, sigusr);
	cpid = fork();
	if(cpid == 0)
	{
		printf("Child Process cpid: %d\n", getpid());
		kill(getppid(), SIGUSR1);
	}
	else if(cpid > 0)
	{
		printf("error\n");
	}
	else if(cpid < 0)
	{
		wait(0);
	}

	return;
}
