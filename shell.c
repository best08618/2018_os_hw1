#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

char* read_command(void);
char** tokenize_command(char* line);


int main(void)
{
	printf("Shell from Jinhwa");
	char buff[1024];
	char* line;
	char** tok_com; 
	while(1){
		getcwd(buff,1024);
		printf("%s" , buff);
		printf(">");
		line = read_command();
		printf("line %s\n", line);
		tok_com = tokenize_command(line);
		printf("tok0: %s\n " ,tok_com[0]);
		return 0 ;
	} 
}

char** tokenize_command(char* line)
{
	char** tok_command=malloc(sizeof(char**));
	int tok_num = 0; 
	char* token = strtok(line," ");
	tok_command[tok_num++] = token; 
	while(token)
	{
		token = strtok(NULL," ");
		tok_command[tok_num] = token;
		tok_num ++ ;
	
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
