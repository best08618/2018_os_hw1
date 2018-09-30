#include "header.h"

int no_full(int path_num){

	for(int i=0; ; i++) {
		if (stat(tok[0],&fstat_buf) == 0) {
			strcpy(new_tok,tok[0]);
			return 0;
			break;
		}
		else{
			strcat(new_path[i],"/");
			strcat(new_path[i],tok[0]);
			strcpy(new_tok,new_path[i]);
			if (stat(new_path[i], &fstat_buf) == 0){
				if (strcmp(tok[0],"echo") == 0) {
					i = 0;
					if (tok[i+1][0] == '$'){
						printf("%s = %s\n",tok[i+1]+1 ,getenv(tok[i+1]+1));
						break;
					}
					else {
						printf("%s\n",tok[i+1]);
						break;
					}
				}
				else {
					return 0;
					break;
				}
			}
			else{
				if(i==path_num){
					if(tok[0]=="space")break;
					if(tok[0]=="cd"){
						if(chdir(tok[1]) == -1){
							perror("cd");
						}
						else{
							break;
						}
					}
					printf("nofile\n");
					break;
				}
			}
		}
	}
}

