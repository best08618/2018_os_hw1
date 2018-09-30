#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE 256
#define SEP "\n\t "
#define BUFSIZE 64

int check_exit(char* token);
int shell_argv(int argc, char** argv, char* input);
void execute(char* s_path, int argc, char** argv);
char* shell_path(int argc, char** argv, char* env);

int main(int argc, char** argv)
{

char* input = NULL;
size_t size = 0;
char* s_path = NULL;
char* env = getenv("PATH");

	printf("Shell Start\n");	

while(1){
	printf("Enter input string: ");

	getline(&input, &size, stdin);

	argc = shell_argv(argc, argv, input);
	s_path = shell_path(argc, argv, env);
	execute(s_path, argc, argv);

	free(s_path);
	printf("Return to main Function\n");
	}
}
	
int shell_argv(int argc, char** argv, char* input) 
{
	char** saveptr = malloc(BUFSIZE * sizeof(char*));
	char* token;

	token = strtok_r(input, SEP, saveptr);

		while(token) 
		{
		check_exit(token);
		strcpy(argv[argc-1], token);
		argc++;
		token = strtok_r(NULL, SEP, saveptr);	
		}

	argv[argc] = NULL;

return argc;
}

int check_exit(char* token)
{
	if(!strcmp(token, "quit"))
		exit(EXIT_SUCCESS);
}

char* shell_path(int argc, char * argv[], char* env)
{
	struct stat fstat_buf;
	int i, j=0;
	char *str;
	int bufsize = BUFSIZE;
	char **token = malloc(BUFSIZE * sizeof(char*));
	char *saveptr;
	int ret;
	char * input;

	if (argc == 1)	{
		printf("usage: getenv env_vars ... \n");
		exit(0);
	}
	else {
		for (i = 0, str=env; i < argc-1 ; i++) {
			for (j=0; ;str= NULL,j++) {

				input = (char *)malloc(BUFSIZE * sizeof(char*));
				token[j] = strtok_r(str, ":", &saveptr);

				if (j >= bufsize) {
					bufsize += BUFSIZE;
			      		token = realloc(token, bufsize * sizeof(char*));
				}
				if (token[j] == NULL){
					printf("No command like that\n");
					exit(EXIT_FAILURE);
				}

				strcat(input, token[j]);
				strcat(input, "/");
				strcat(input, argv[0]);
				ret = stat(input, &fstat_buf);
				if (ret == 0){
					return input;}
				input = NULL;
				free(input);
			}
		}
	if (ret == -1)
		printf("No command like that\n");
		exit(EXIT_FAILURE);	
	}
}

void execute(char* s_path, int argc, char *argv[])
{
	pid_t pid = -1;

	pid = fork();
	
	if(pid == -1){
		perror("fork error");
		exit(0);
	}
	else if(pid == 0){
		argv[0] = s_path;
		execve(s_path, argv, NULL);
		printf("exec failed\n");
		exit(0);
	}
	else{
		wait(0);
		printf("Command complete\n");
	}
}


