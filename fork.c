#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pid_t pid = -1;
	int i;
	pid_t * child_pids = NULL;

	for(i=0;i<10;i++){

	pid = fork();
	if (pid == -1) {
		perror("fork error");
		return 0;
	} else if (pid == 0) {
		// child!
		printf("child process with pid %d\n",getpid());
		// do some great job!, which is currently sleep
		sleep(1);
		return 0;
	} else {
		if (child_pids == NULL) {
			child_pids = (pid_t *)malloc(sizeof(pid_t)*10);
			// stores 10 children's pid
			memset(child_pids, 0, sizeof(*child_pids));
		}
		// parent!
		printf("parent(%d): child(%d) has created\n", getpid(), pid);
		child_pids[i] = pid;
	}
	}

	for (i = 0 ; i < 10 ; i++) {
		int status;
		// wait for all the child processes' completion
		waitpid(child_pids[i], &status, 0);
		printf("parent(%d): child(%d) has completed\n", getpid(), child_pids[i]);
	}
	return 0;

}

