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

void printInfo();
char *checkInput(char *input);
void execute(char *input);

void main()
{
	size_t inputSize = 50;
	char *input;
	input = (char *)malloc(inputSize * sizeof(char));

	while(1)
	{
		//print user info, time, PWD
		printInfo();

		//getline
		getline(&input, &inputSize, stdin);

		//stat check the input in $PATH
		input = checkInput(input);

		//if exist fork() and exec on child
		execute(input);
	}
}

void printInfo()
{
	printf(">");
	return;
}

char *checkInput(char *input)
{
	if(strcmp(input, "quit\n") == 0)
	{
		exit(0);
	}
	else if(*input == '/')
	{

	}
	else
	{

	}
}

void execute(char *input)
{
	if(*input == '/')
	{		

	}
	else
	{
		printf("%s", input);
		return;
	}
}
