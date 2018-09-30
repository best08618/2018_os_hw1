#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

char line[100];				// save the user command
char *tokens[100];			// save the tokenized command
int NO_EXECUTE = 0;			// If you use getenv function or put a wrong command -> 1

void read_line(void);
void split_line(void);
void search_process(void);
void execute(void);

void main ()
{
	while(1)
	{
		read_line();
		split_line();		
		search_process();
		execute();
	}
}

void read_line(void)
{
	printf("INPUT THING : ");
	NO_EXECUTE = 0;
	gets(line);
	if (strcmp(line, "quit") == 0)
	{
		exit(0);
	}
}

void split_line(void)
{
	char *token = NULL;
	int position = 0;

	token = strtok(line, " ");
	tokens[position] = token;
	position++;

	while(token != NULL)
	{
		token = strtok(NULL, " ");
		tokens[position] = token;
		position++;
	}
}

void search_process(void)
{
	struct stat stat_buf;
	int value;			// return value of stat
	int PATH_VALUE = 0;
	char *savearray = NULL;		// path saving array
	char *savearray2[100];		// tokenized path saving array
	char savepath[256];		// new path saving array

	char *temp = NULL;
	int position = 0;
	char *token = NULL;
	char *saveptr = NULL;

	if(*(tokens[0]) != '/') // Find the path using 'getenv'
	{
		if(isupper(*(tokens[0])) != 0) 	// Just Using 'getenv'
		{
			savearray = getenv(tokens[0]);
			printf("%s : %s\n", tokens[0], savearray);
			NO_EXECUTE = 1;
			return;
		}

		else if(strcmp(tokens[0], "cd") == 0)
		{
			chdir(tokens[1]);
			NO_EXECUTE = 1;
			return;	
		}

		savearray = getenv("PATH");
		strcpy(savepath, savearray);  /// initialize the path

		for (position = 0, token = savepath; ; token= NULL, position++) {
			savearray2[position] = strtok_r(token, ":", &saveptr);
			if (savearray2[position] == NULL)
				break;
		}

		position++;
		for(int i = 0; i< position; i++)
		{
			temp = (char*)malloc(strlen(savearray2[i])-1);

			strcpy(temp, savearray2[i]);
			strcat(temp, "/");
			strcat(temp, tokens[0]);	
			value = stat(temp, &stat_buf);
			PATH_VALUE++;

			if(value == 0){
				tokens[0] = temp;	
				return;
			}
			else if(PATH_VALUE == i){
				NO_EXECUTE = 1;
				printf("Wrong Command\n");
				return;
			}
		}	
	}
	else	// case of using "/"
	{	
		value = stat(tokens[0], &stat_buf);
		if(value == 0)
			return;	
		else
			perror("stat error\n");	
	}	
}
void execute(void)
{
	if(NO_EXECUTE == 1)
		return;
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		execve(tokens[0] , tokens , NULL );
	}
	else if (pid > 0){
		wait(0);
	}
	else if (pid < 0){
		perror("fork error");
	}
}
