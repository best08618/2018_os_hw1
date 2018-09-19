#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int i=0 ;
	do{
	pid = fork();
	if (pid == -1) {
		perror("fork error");
		return 0;
	}
	else if (pid == 0) {
		// child
		i =0 ;
		printf("%d" , i);
		printf("child process with pid %d\n",getpid());
//		return 0;
	} 
	else {
		printf("my pid is %d\n", getpid());
		i++;
		wait(0);
	}
	}while(i > 0 && i < 5 );
	return 0;
	
}

