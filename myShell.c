#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	char input[15];
	const char *path = getenv("PATH");

	printf("\n\twelcome to javier's shell :D\n\n");


	while(1){

		printf(">");
		scanf("%s", input);

		if(strcmp(input, "\n")==0) { /*nothing*/ }

		else if(strcmp(input, "quit")==0) {
			printf("\t<good bye!\n");
			break;
		}

		//run a program, look in all directories
		else {
			char *temp, *tok[100];
			char *str = path; //so i dont mes the original one
			int i = 0;

			printf("%s \n\n",str);

			/*
			first I try just to print the adres of the programs
			later i can figure out how to run them
			*/
			tok[1] = strtok(str, ":");
			while(tok[i] != NULL && i<10) {

				printf("%s/%s\n", tok[i], input);
				tok[i] = strtok_r(str, ":",&temp);
				i++;
			}


			printf("***---------------------***\n");

		}
	}

	return 0;
}
