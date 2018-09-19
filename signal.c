#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

//sample signal program
//0. set signal handler
//1. fork child
//2. child sends signal back to parent

void sig_usr(int signum)
{
	//signal handler for SIGUSR1
	printf("GOt signal %d\n", signum);
	exit(0);
}

int main(int argc, char *argv[])
{
	pid_t cpid;
	//0. set signal handler
	signal(SIGUSR1, sig_usr);

	//1. fork child
	cpid = fork();
	if(cpid == 0) {
	//child
	printf("sending sig to parent \n");
	kill(getpid(), SIGUSR1);
	exit(0);
	} else if (cpid > 0) {
	//parent
	wait(0);
	} else {
	//err
	perror("fork");
	}
}
