#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

#define TOK_BUFSIZE 64
#define LINE_BUFSIZE 1024	

char* read_line()
{
	/*char *line = NULL;
	gets(line);
	printf(">> %s", line);
	return line ;*/

	int bufferSize = LINE_BUFSIZE;
	int num =0;
	int charac;
	char* buffer = malloc(bufferSize * sizeof(char*));
	if(!buffer)
	{
		printf("allocation error");
        exit (0);
	}
	
	while(1)
	{
		charac = getchar();
		
		//reach END OF FILE, terminate with null and return
		if(charac == EOF || charac == '\n')
		{
			buffer[num] = '\0';
			return buffer;
		}
		else
		{
			buffer[num] = charac;
		}
		num++;
	}
}


char** parse_line(char* line)
{

	int bufferSize = TOK_BUFSIZE;
	int tok_num = 0;
	char **ppArguList = malloc (bufferSize * sizeof (char*));
	char *pToken;

	if(!ppArguList)
	{
		printf("allocation error");
		exit (0);
	}

	//parse line into token
	pToken = strtok(line, " ");
	
	while(pToken != NULL)
	{
		//sort tokens into argu list
		ppArguList[tok_num]=pToken;
		tok_num++;

		if(tok_num>=bufferSize)
		{
			bufferSize += TOK_BUFSIZE;
			ppArguList = realloc(ppArguList, bufferSize * sizeof (char*));
			if(!ppArguList)
    		{
        		printf("allocation error");
        		exit (0);
    		}
		}

		//continue scanning the line while the first call ended
    	pToken = strtok(NULL, " ");
	}
	//free ppArguList
	ppArguList[tok_num] = NULL;
	return ppArguList;
}


int execute(char** argv)
{
	pid_t pid;
	int status;

	pid = fork();
	
	if(pid<0)
	{
		perror("ERROR: Fork failed\n");
		exit(1);
	}
	//child process
	else if(pid == 0)
	{
		//execute the command, if anything is returned, error
		if(execvp(*argv, argv)<0)
		{
			perror("ERROR: Exec failed\n");
			exit(1);
		}
	}
	//parent process
	else
	{
		while(wait(&status) != pid);
	}
}

void command_loop()
{
	//read, parse, execute
	char *line;
	char **args;
	int status;

	while(status)
	{
		line = read_line();
		args = parse_line(line);
		status = execute(args);
	}

	free(line);
	free(args);
}

int main(int argc, char **argv)
{
	printf("Shell program starts here -> \n");
	while(1)
	{
		command_loop();
	}
	return 0;
}



