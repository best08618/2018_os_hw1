#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void sign_callback_handler(int signum)
{	
	printf("Signal %d\n", signum);
	exit(0);
}


int main(int argc, char *argv[])
{
	signal(SIGUSR, sign_callback_handler);
	pid_t cpid;

	//fork child
	cpid = fork();
	if(cpid == 0)
	{
		printf("Send signal to parent \n");
		kill(getppid(), SIGUSR);
		exit(0);
	}
	else if(cpid>0)
	{
		wait(0);
	}
	else
	{
		perror("Fork\n");
	}
}
