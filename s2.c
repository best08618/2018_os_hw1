#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int quit;
char f_str[20];
char tcopy[200];
char *f_str1;
char *pathtok[100];
char *tok[10],*saveptr;
struct stat fstat_buf;
void in_path();
void ffork();


int main (){

	while(1){
		in_path();
		if (quit==0) return 0;
		ffork();
	}
	return 0;
}

void in_path(){

	char *env, *str;
	int i , j, k = 0;
	char pcopy[200];
	int ret;

	printf("<Simple Shall> ");
	fgets(f_str,sizeof(f_str),stdin); 
	f_str[strlen(f_str)-1] = '\0';

	for (i=0,f_str1=f_str; ;f_str1=NULL,i++){
		tok[i] = strtok_r(f_str1," ",&saveptr);
		if (tok[i]=='\0') break; 	
		quit = strcmp(tok[0],"quit"); 
		if (quit==0) break;
	}

	if (tok[0][0]>='A'&&tok[0][0]<='Z'){
		env = getenv(tok[0]);
		strncpy(tcopy,env,200);
		printf("%s = %s\n",tok[0],env);
	}
	else{
		for (j=0; j < i ; j++){
			env = getenv("PATH");
			strncpy(pcopy,env,200);
			
			for (k=0,str=pcopy; ; str = '\0',k++){
				pathtok[k] = strtok_r(str,":",&saveptr);
				if (pathtok[k]==NULL) break;
			}
			
			for (k=0; ; k++){
				strncpy(tcopy,pathtok[k],100);
				if (tcopy==NULL) {break;}
				strcat(tcopy,"/");
				strcat(tcopy,tok[0]);
				ret = stat(tcopy, &fstat_buf);
				if (ret == -1){
			//		perror("stat");
				}
				else {
					return ;	
				}
			} 
		}}
	return;
}

void ffork(){

	pid_t pid;
	pid = fork(); 
	if (pid == -1) { 
		printf("aa");
		perror("fork error");
		return ;
	}
	else if (pid == 0) {		// child
		execve(tcopy,tok,NULL);
		exit(0);
	} 
	else {		// parent
		wait(0);
	}
	return;
}
