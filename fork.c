#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();//fork generate 
	if (pid == -1) { //if pid = -1 -> fork error
		perror("fork error");
		exit 0;
	}
	else if (pid == 0) {
		int j;
		for(j = 0; j < 10; j++) {
	// child process 0 return
			printf("child process with pid %d\n", 
			getpid());
			sleep(1);

	}
	exit(0);
}	
	 else {
		// parent process
		int i;
		for (i = 0; i<10; i++) {
			printf("my pid is %d\n", getpid());
			sleep(1);
	}
	exit(0);
}
	return 0;
}

