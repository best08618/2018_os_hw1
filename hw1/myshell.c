#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>


//function
int printSiSH();
int stat_file();
int getenv_var();
void token();
int path_token();
int execute();

//global variable
char* str[40];
char* basic_path;
char store_path[70][70];
char* basic[100];
int str_num, num_path;
char command[256];
char* findpath;
char** argv_cpy;
typedef struct tm time_str;


int main(int argc, char *argv[]){
	num_path=0;
	memset(store_path,0,sizeof(store_path));
	path_token();

	while(1){
		memset(str,0,sizeof(str));
		str_num=0;
		printSiSH();

		fgets(command,sizeof(command),stdin);
		command[strlen(command)-1]='\0';

		if((strcmp(command, "quit")==0))
			break;

		token(command);

		if(str[0][0]=='$'){
			getenv_var();
		}
		else{
			int find = stat_file();
			if(find==0){
				execute();
			}
			else if(find==-1){
				printf("cannot find program\n");
			}
		}
	}
	return 0;
}

int execute(){
	pid_t pid;
	pid=fork();

	if (pid == -1) {
		perror("fork error");
		exit(0);
	}
	else if(pid==0){
		int ex_err = execve(findpath, str ,NULL);
		if(ex_err==-1){
			printf("execve err\n");
		}
		exit(0);
	}
	else{
		wait(0);
	}
	return 0;
}


int path_token(){
	char *saveptr, *str_var;
	char save_path[200];
	int j=-0;

	basic_path=getenv("PATH");
	strcpy(save_path,basic_path);

	for (j=0,str_var=save_path; ;str_var=NULL,j++) {
		basic[j] = strtok_r(str_var, ":", &saveptr);
		if (basic[j] == NULL)
			break;
		strcpy(store_path[j],basic[j]);
		num_path++;
	}
	num_path--;
	return 0;
}

int printSiSH(){
	char prompt[80];
	getcwd(prompt, 80);
	fprintf(stdout,"SiSH %s ",prompt);
	return 0;
}

void token(char* command){
	char *next, *token_str;
	str_num=0; 

	while(1){
		str[str_num] = strtok_r(command, " ", &next);
		if(str[str_num]==NULL)
			break;
		command=NULL;
		str_num++;
	}
	return ;
}

int getenv_var(){
	char *env;
	char newenv[10];
	if(strcmp(str[0]+1,"TIME")==0){
		time_t  today_time;
		time_str* today;
		time(&today_time);

		today = localtime(&today_time);
		printf("[TIME] %d:%d:%d \n", today->tm_hour, today->tm_min,today->tm_sec);	
	}			
	else{
		strcpy(newenv,str[0]+1);
		env = getenv(newenv);
		printf("%s=%s\n", newenv, env);
	}

	return -1;
}

int stat_file(){
	struct stat fstat_buf;
	int ret, ret1;

		int i=0;
		while(1){
			if(basic[i]==NULL){
				break;
			}
			if(strcmp(str[0],"cd")==0){
				char cwd[100];
				getcwd(cwd,sizeof(cwd));
				chdir(str[1]);
				getcwd(cwd,sizeof(cwd));
				return 2;
			}

			char newpath[20];
			findpath = (char*)malloc(sizeof(int)*100);

			ret1 = stat(str[0], &fstat_buf);
			if(ret1==0){
				strcpy(findpath,str[0]);
				return 0;
			}
			strcpy(newpath,store_path[i]);
			strcat(newpath,"/");
			strcat(newpath,str[0]);
			ret = stat(newpath, &fstat_buf);
			i++;

			if(ret==0){
				strcpy(findpath,newpath);
				return 0;
			}
			if(i==num_path){
				printf("no file\n");
				return -1;
			}
		}
	return 0;
}

