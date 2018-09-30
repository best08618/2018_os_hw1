#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

void commandtok();
int Getenv();
int Fork();
void Time();

char forkstr[100];
char* inputtok[50];
char command[100];

int main()
{
	int stat_check;		
	printf("SISH start\n");

	while(1){
		char* input;
		input = (char*)malloc(sizeof(char)*50);	
		printf("Enter the input : ");
		fgets(input, 100, stdin);
		input[strlen(input)-1]='\0';
		strcpy(command,input);
		
		if(!strncmp(command, "quit",4)){
			printf("SISH Finish\n");
			break;
		}
					
		commandtok(command);	
		stat_check = Getenv(command);

		if(stat_check == 1){	
			Fork();
		}else if(stat_check == 2){
		}else{
			printf("%s: command not found\n", command);
		}		
	}
	return 0;
}

void commandtok(char* command)
{
	char *save;
	int i = 0;
	int len = 0;

	for(i=0; ;command=NULL,i++){
		inputtok[i] = strtok_r(command, " ", &save);
		if(inputtok[i] == NULL)
		break;
	}	
	return ;	
}

int Getenv()
{
	struct stat fstat_buf;
	int i, j, n=0;
	char *env, *str;
	char *tok[100], *saveptr;
	char getstr[100];
	char newstr[100];
	char realenv[100];
	char* ptr = getstr;
	int stat_find;
	int k=0;
	char var1[100];
	

	if(!strncmp(command, "/",1)){
		stat_find = stat(command, &fstat_buf);
		if(stat_find == 0){
			strcpy(forkstr, command);
			return 1;
		}else return 0;
	}

	env = getenv("PATH");
	strcpy(realenv,env);
	for(j=0, str=realenv; ;str = NULL,j++){
		tok[j] = strtok_r(str, ":", &saveptr);
		
		if(tok[j] == NULL) break;

		strcpy(getstr, tok[j]);
		strcat(getstr, "/");
		strcat(getstr, inputtok[0]);

		if(!strncmp(command,"cd",2)){
			chdir(inputtok[1]);
			return 2;
		}else if(!strncmp(command,"TIME",4)){
			Time();
			return 2;		
		}
			stat_find = stat(getstr, &fstat_buf);

			if(stat_find == 0){
				strcpy(forkstr, getstr);
				return 1;
			}
		memset(getstr, 0, sizeof(getstr));
		memset(newstr, 0, sizeof(newstr));
	}
	return 0;
}
	
int Fork()
{
	pid_t pid;
	pid = fork();	
		if(pid < 0){
			perror("Fork Error");
			exit(0);
		}
		else if(pid == 0){
			execve(forkstr, inputtok, NULL);
			exit(0);
		}
		else{
			wait(0);
		}
	return 0;
}

void Time()
{
	time_t now_time;
	struct tm *now_date;
	char arr[50];
	time(&now_time);

	now_date = localtime(&now_time);
	strcpy(arr, asctime(now_date));
	puts(arr);
	return ;
}

