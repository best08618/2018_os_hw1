#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
//#include <linux/limits.h> //

//global variable
int path_num = 0;
char currLoc[255], input[40], new_tok[200];
char *tok[100], *new_token[100];
char new_path[100][100];

//struct
struct stat fstat_buf;

//function
void execSiSH();
void token();
void print_env();
void tok_path();
int no_full();
int fork_exec();
int cdir();
void c_Time();
//main
int main(int argc, char *argv[])
{
	while(1) {
		execSiSH();
		token();
		if(tok[0][0] =='$'){
			print_env();
		}
		else {
			tok_path();
			if(no_full()==0){
				fork_exec();
			}
		}
	}
	return 0;
}

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

void token(){
	int j = 0;
	char *saveptr;
	char* str;
	for (str=input; ;str= NULL,j++) {
		tok[j] = strtok_r(str, " ", &saveptr);
		if (tok[j] == NULL) {
			if (tok[0] == NULL) {
				tok[0] = "space";
			}
			break;
		}
	}
}

void print_env(){
	printf("%s = %s \n",tok[0]+1,getenv(tok[0]+1));
}

void tok_path(){
	char* path_str = getenv("PATH");
	char *path_saveptr,*path_tok[100];
	char* path_copy;
	path_copy = (char*)malloc(sizeof(char)*256);
	strcpy(path_copy,path_str);
	for (int j=0; ;path_copy=NULL,j++) {
		path_tok[j] = strtok_r(path_copy, ":", &path_saveptr);
		path_num++;
		if (path_tok[j] == NULL) break;
		strcpy(new_path[j], path_tok[j]);
	}
}

int no_full(){
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
						printf("%s = %s\n",tok[i+1]+1,getenv(tok[i+1]+1));
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
						if(cdir()==1)break;
					}
					printf("nofile\n");
					break;
				}
			}
		}
	}
}

int fork_exec(){
	pid_t pid;
	pid = fork();
	if (pid == -1) {
		perror("fork error");
		exit(0);
	}
	else if (pid == 0) {
		int result = 0;
		result = execve(new_tok,tok,NULL);
		return 0;
	}
	else wait(0);
	return 0;
}

int cdir(){
	if(chdir(tok[1]) == -1){
		perror("cd");
		return 0;
	}
	return 1;
}
