#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int main(int argc, char *argv[])
{
	int i=0;
	pid_t pid;
	
	char *new_argv[300];
	char _argv[300];

	int new_argc;//For storeing modified argc
	char *save_ptr;//Pointer for storing location of next processing becuase of strtok_r
	char *tok_path;//Pointer that parsing the PATH and get the result
	char save_path[300];//For get PATH 
	char new_path[300];//For redirect and store the PATH

	char command[300];//Variable for storing the input command

	struct stat fstat_buf;
	int ret;
	
	new_argc = argc;

	while(1){
		if(new_argc == 1){
			printf("Please enter the command:");
			fgets(_argv, sizeof(_argv), stdin);

			new_argv[0] = strtok_r(_argv, " ", &save_ptr);
		
			for(i=1; ; i++){
				if(!(new_argv[i] = strtok_r(NULL, " ", &save_ptr)))
					break;
				new_argc++;
			}
			new_argv[new_argc-1] = strtok_r(new_argv[new_argc-1], "\n", &save_ptr);
			new_argv[new_argc] = (char* )NULL;
			strcpy(command, new_argv[0]);
			if(strcmp(command, "exit") == 0){
				return 0;
			}
		}
		else{
			for(i=0; i<new_argc; i++){
				if(i == new_argc-1){
					new_argv[i] = (char*) NULL;
				}
				else{
					new_argv[i] = argv[i+1];
				}
			}
			strcpy(command, argv[1]);
		}

	strcpy(save_path, getenv("PATH"));
	tok_path = strtok_r(save_path, ":", &save_ptr);
	strcpy(new_path, tok_path);
	strcat(new_path, "/");
	strcat(new_path, command);

	pid = fork();

		if(pid == -1){
			printf("process fork fail \n");
			return -1;
			}
			else if(pid == 0){
				while(execve(new_path, new_argv, environ) == -1){
					if(!(tok_path = strtok_r(NULL, ":", &save_ptr)))
						break;
					strcpy(new_path, tok_path);
					strcat(new_path, "/");
					strcat(new_path, command);
				}
				exit(0);
			}
			else{
				wait(0);
			}
			new_argc = 1;
		}
}
