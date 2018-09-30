#include "header.h"

int tok_path(){
	char* path_str = getenv("PATH");
	char *path_saveptr,*path_tok[100];
	char* path_copy;
	int path_num=0;
	path_copy = (char*)malloc(sizeof(char)*256);
	strcpy(path_copy,path_str);
	for (int j=0; ;path_copy=NULL,j++) {
		path_tok[j] = strtok_r(path_copy, ":", &path_saveptr);
		path_num++;
		if (path_tok[j] == NULL) break;
		strcpy(new_path[j], path_tok[j]);
	}
	return path_num;
}

