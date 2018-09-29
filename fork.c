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

	for(i = 0; i < 10; i++)
	{

	pid = fork();

	if (pid == -1) {
		perror("fork error");
		return 0;
			}

	else if (pid == 0) {
	// Child
		printf("child process with pid %d\n",getpid());
		sleep(1);
		return 0;
			}

	else 	{
		if (child_pids == NULL) {
			child_pids = (pid_t *)malloc(sizeof(pid_t)*10);
			memset(child_pids, 0, sizeof(*child_pids));
				}
		// Parent
		printf("parent(%d): child(%d) has created\n", getpid(), pid);
		child_pids[i] = pid;
		}
	}

	for (i = 0 ; i < 10 ; i++) {
		int status;
		int wpid = -1;
		wpid = child_pids[9-i];
		waitpid(wpid, &status, 0);
		printf("parent(%d): child(%d) has completed\n", getpid(), wpid);
	}

	return 0;
}

