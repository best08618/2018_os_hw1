#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	for(int i =0; i<10; i++){
		pid = fork();
		if(pid == 0 ){
			//child
			printf("child %d\n",i+1);
			break;
		}
	}

	return 0;
}

