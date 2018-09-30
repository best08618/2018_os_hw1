#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char * argv[])
{
	char *tok[100], *temp;
	printf("\n\twelcome to javier's shell :D\n\n");


	while(1){
		char *input;

		printf("  >");
		scanf("%s", input);

		if(strcmp(input, "quit")==0) {
			printf("\t<good bye!\n");
			break;
		}

		else /*look for a program in all directories*/ {

			char *var = getenv("PATH");
			char *path;
			int flag;
			struct stat buf;
			//buf = malloc(sizeof(struct stat));

			for(int i=0; i<38; i++, var=NULL) {
				*tok = strtok_r(var, ":", &temp);
				if(*tok==NULL){break;}

				strcpy(path, *tok);
				strcat(path, "/");
				strcat(path, input);
				printf("%s\n", path);


				if (stat("/mnt/c/Users/franc/projects/2018_os_hw1/README.md", &buf)) {
					printf("%s","it exist\n");
    				}
				else{
					printf("%s","does not exist\n");
				}

			}
			printf("\n");
			//free(buf);
		}
	}

	return 0;
}

