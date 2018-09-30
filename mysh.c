#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>
#define MAX_STRING_SIZE 100

char* tok[40];
char* get_token[40];
char str_read[MAX_STRING_SIZE];
struct stat fbuf;
char *get2;

void token();
void get_env();
void finding_file();
int fork_execv();
int case_comparison();

int main(){
	get_env();
	while(1){

		fgets(str_read, MAX_STRING_SIZE, stdin);
		printf("Command : %s\n", str_read);
		str_read[strlen(str_read)-1] = '\0';
		
		if( (strcmp(str_read, "quit") == 0) )
		{
		 return 0;
		}
		
		int res = case_comparison(str_read);
		if(res){
			token();
			finding_file();
		}

	}	
	return 0;
}

void token(){

	char* next;
	char* str;

	str = (char*)malloc(sizeof(char)*30);
	strcpy(str, str_read);

	for(int i = 0; ;str = NULL, i++){
		tok[i] = strtok_r(str, " ", &next);
		if(tok[i] == NULL) break;
		printf("\t%s\n", tok[i]);
	}
	return ;		
}

void get_env(){
	
	int i = 0;

	char *str, *str_copy;
	char *next, *copy;
	str = getenv("PATH");
	printf("%s\n", str);
	str_copy = (char*)malloc(sizeof(char)*300);
	strcpy(str_copy, str);
	
	copy = str_copy;
	while(1){
		get_token[i] = strtok_r(copy, ":", &next);
		if(get_token[i] == NULL) break;
		printf("%s\n", get_token[i]);
		i++;
		copy = NULL;
	}
	free(str_copy);
	return ;
}

void finding_file(){
	
	char *string_copy1 = "/";
	char *string_copy2 = malloc(sizeof(char) *100);
	
	for(int a = 0; ; a++){ 
	if(get_token[a] == NULL) break;
		strcpy(string_copy2, get_token[a]);
		strcat(string_copy2, string_copy1);
		strcat(string_copy2, tok[0]);
		
		int ret = stat(string_copy2, &fbuf);
		if(ret == -1) printf(" -> file does not exist \n");
		if(ret == 0){
			printf(" -> file exist \n");
			fork_execv(string_copy2);
			break;
		}
	}
	free(string_copy2);

	return ;
}

int fork_execv(char *string_copy2){
	
	pid_t pid;
	pid = fork();
        
	if (pid == -1){
                perror("fork error");
                return 0;
        }
        else if (pid == 0) { //child
		execve(string_copy2, tok, NULL);
		return 0;
	}
	else {//parent
                wait(0);
		return 0;
        }
        return 0;
}

int case_comparison(){
	
	char ch = str_read[0];
	
	if(ch >= 'A' && ch <= 'Z'){
		get2=getenv(str_read);
		printf("%s\n",get2);  
		return 0;
	}
	else{
		return 1;
	}
}

