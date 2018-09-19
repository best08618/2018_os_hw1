#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i = 0;
	pid_t pid[10];
	for(i = 0; i < 10; i++)
	{
		cpid[i] = fork();
		if(cpid[i] == 0)
		{
			printf("cpid: %d\n", getpid());
			exit(0);
		}
		else if (cpid[i] < 0)
		{
			printf("ERROR\n");
			exit(0);
		}
		else
		{
			
		}
	}
	return 0;

/*
	pid_t pid;

	pid = fork();
	if (pid == -1) {
		perror("fork error");
		return 0;
	}
	else if (pid == 0) {
		// child
		printf("child process with pid %d\n", 
			getpid());
	} else {
		// parent
		printf("my pid is %d\n", getpid());
		wait(0);
	}
	return 0;
*/
}

