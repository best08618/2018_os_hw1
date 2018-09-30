#include "header.h"

void execSiSH(){
	getcwd(currLoc,255);
	printf("SiSH %s$ ",currLoc);
	fgets(input,sizeof(input),stdin);
	input[strlen(input)-1]='\0';
	memset(new_path,0,sizeof(new_path));
	if (strcmp(input,"quit") == 0) {
		printf("program is exit\n");
		exit(0);
	}
}

