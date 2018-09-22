#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>

/* $PATH directories
/mips-tools/bin/
/usr/local/sbin/
/usr/local/bin/
/usr/sbin/
/usr/bin/
/sbin/
/bin/
/usr/games/
/usr/local/games/
/snap/bin/
*/

void main(int argc, char *argv[])
{
	pid_t cpid;
	size_t inputSize = 32;
	char *input;
	input = (char *)malloc(inputSize * sizeof(char));

	while(1)
	{
		//print user info, time, PWD
		printf(">");

		//getline
		getline(&input, &inputSize, stdin);
		printf("%s", input);
		if(strcmp(input, "quit\n") == 0)
		{
			exit(0);
		}

		//string tokenize

		//stat check the input in $PATH

		//if exist fork() and exec on child
	}
}
