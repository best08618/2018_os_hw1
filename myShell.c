#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	char input;
	const char *path = getenv("PATH");

	printf("welcome to javier's shell :D\n\n");


	while(1){

		printf(">");
		scanf("%s", &input);

		if(*input=='\0'){ /*nothing*/ }

		else if(*input=="quit"){ break; }

		//run a program, look in all directories
		else {
			char *str = *path; //so i dont mes the original one
			char *tok = NULL;

			tok = strtok(str, ":");
			while(tok != NULL) {
				printf("\t%s...%s\n", tok, input); //for now i just want to print it, later i can  actually run it
				tok = strtok(str, ":");
			}
		}
	}

	return 0;
}
