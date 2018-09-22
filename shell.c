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
	char input[50] = NULL;

	while(1)
	{
		//print user info

		//getline

		//string tokenize

		//stat check the $PATH

		//if exist fork() and exec on child
	}

	return;
}
