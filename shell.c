#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

char* read_command(void);
int main(int argc, char ** argv)
{

	char* line;
	char** args;
	int status ; 
	while(1){
		printf(">");
		line = read_command();
		printf("line %s", line);
		return 0 ;
	}
 

}
char* read_command(void)
{
 	int bufsize =1024;
	int position = 0;
	char * buffer  = malloc(sizeof(char)* bufsize);
	int character;
	if(!buffer){
		printf("allocation error");
		exit(0);
	}
	while(1)
	{
		character= getchar();
		if( character == '\n'){
			buffer[position] = '\0';
			return buffer;
		}
		else{
			buffer[position] = character;
		}
		position ++ ;
	}

}
