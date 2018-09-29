#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int i, j=0;
	char *env, *str;
	char *tok, *saveptr;
	if (argc == 1)	{
		printf("usage: getenv env_vars ... \n");
		return 0;
	} else {
		for (i = 0 ; i < argc-1 ; i++) {

			env = getenv(argv);
			for (str=env; tok != NULL; str = NULL) {
				tok = strtok_r(str, ":", &saveptr);
				printf("%s\n", tok);
			}
			printf("***---------------------***\n");
		}
	}

	return 0;
}
