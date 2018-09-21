#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void signal_callback_handler(int signum)
{
	printf("signal");
	printf("Caught signal %d \n",signum);
	return ;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, signal_callback_handler);
	pid_t pid;
	int i=0 ;
	while(i< 5) {
	pid = fork();
	if (pid == -1) {
		perror("fork error");
		return 0;
	}
	else if (pid == 0) {
		//child
		kill(getppid(),SIGINT);
		printf("child process with pid %d\n", getpid());
		return 0;
	} 
	else {
		//parent
		printf("my pid is %d\n", getpid());
		i++;
		wait(0);
	}
	}
	return 0;
	
}

