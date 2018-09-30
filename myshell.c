#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int atgc, char *argv[])
{
    while(1){
        char *line = NULL;
        if (getline(&line, NULL, stdin) == -1) {
            printf("Error\n");
        } else {
	   //do something useful
	   free(line);
        }
       // parsecmd(cmd,argv);
    }
    return 0;
}