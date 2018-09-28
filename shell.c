#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


char* read_command(void);
char** tokenize_command(char* line);
int execute(char** comm);

int main(void)
{
	printf("Shell from Jinhwa");
	char buff[1024];
	char* line;
	char** tok_com; 
	int flag = 1 ;
	while(flag){
		getcwd(buff,1024);
		printf("%s" , buff);
		printf(":");
		line = read_command();
		tok_com = tokenize_command(line);
		flag = execute(tok_com);
	} 
}

int execute(char** comm)
{
	pid_t pid;
	int stat;
	if(strncmp(comm[0],"quit",4)==0)
		exit(0);
	
	pid= fork();
	if( pid ==0 ){
	// child process
		if(execvp (comm[0],comm) == -1)
		{
		//there are no FILE
			perror("execvp error");
		}
		exit(EXIT_FAILURE);
	}
	else{
	//prent
		wait(0);	
	}

}

char** tokenize_command(char* line)
{
	char** tok_command=malloc(sizeof(char**));
	int tok_num = 0; 
	char* token = strtok(line," ");
	char* tp;
	tok_command[tok_num++] = token; 
	while(token)
	{
		token = strtok(NULL," ");
		tok_command[tok_num] = token;
		tok_num ++ ;
	
	}
	if((tok_num>2) &&(tok_command[1][0] == '$'))
	{	
		char* tp = tok_command[1] + 1 ;
		tok_command[1] = getenv(tp);
	}	
	return tok_command;
}

char* read_command(void)
{
 	int bufsize =1024;
	int size = 0;
	char * buffer  = malloc(sizeof(char)* bufsize);
	int character;
	/*if(!buffer){
		printf("allocation error");
		exit(0);
	}*/
	while(1)
	{
		character= getchar();
		if( character == '\n'){
			buffer[size] = '\0';
			return buffer;
		}
		else{
			buffer[size] = character;
		}
		size ++ ;
		if(size >= bufsize){
			bufsize += 1024;
			
		}
	}

}
