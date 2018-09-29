#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

#define MAX_STR_SIZE 256
void str_read_token();
void path_token();
int fork2(char* copy_path);

char str_read[MAX_STR_SIZE];
char *token_str_read[MAX_STR_SIZE];
char *token_getenv_path[MAX_STR_SIZE];
char getenv_path[300];
char *new_argv[MAX_STR_SIZE];
char* get;
char* get2;

int main(int argc, char *argv[]){
	struct stat fstat_buf;
        while(1){
                printf("jjs15@SiSH:");
                fgets(str_read,MAX_STR_SIZE,stdin);
		str_read[strlen(str_read)-1]='\0';
		
		
	if(str_read[0]>='A' && str_read[0]<='Z'){
		get2= getenv(str_read);
		printf("%s\n",get2);
		}
		else{


                	if(strcmp(str_read,"quit")==0){
                       	 return 0;
                	}

                	else
		str_read_token();


		get= getenv("PATH");
		strcpy(getenv_path,get);
	      //printf("path : %s \n",getenv_path);
		path_token();
		
		


                for(int i=0; ;i++){
		 if (token_getenv_path[i] == NULL) break;
       		 }
		for(int i=0; ; i++){
			
			char copy_path[300];
			memset(copy_path,0,sizeof(copy_path));
			if(token_getenv_path[i]==NULL){
                        printf("no file\n");
                        break;}

			strcat(copy_path,token_getenv_path[i]);
			strcat(copy_path,"/");
        		strcat(copy_path,token_str_read[0]);
			
			int res = stat(copy_path,&fstat_buf);
			if(res==-1){
			//	perror("stat");
			}
			else if(res==0){
			//	printf("file exist \n");
				fork2(copy_path);
				break;
				}
			}
		
		}
	}
        return 0;
}
void str_read_token(){
	char *next;
	char *str;
	int j;
	 for (j=0,str=str_read; ;str= NULL,j++) {
             token_str_read[j] = strtok_r(str, " ", &next);
             if (token_str_read[j] == NULL) break;
            // printf("\t%s\n", token_str_read[j]);
}
return ;
}

void path_token(){
	char *str;
	char *next;
	int j;
	 for (j=0,str=getenv_path; ;str= NULL,j++) {
                                token_getenv_path[j] = strtok_r(str, ":", &next);
                                if (token_getenv_path[j] == NULL) break;
                            //    printf("\t%s\n", token_getenv_path[j]);
                        }
}



int fork2(char* copy_path){
	pid_t pid;
	pid = fork();
        if (pid == -1) {
                perror("fork error");
                return 0;
        }
        else if (pid == 0) {
                // child
		//printf("exe\n");
		execve(copy_path,token_str_read,NULL);                
		exit(0);

        } 
	else {
                // parent        
                wait(0);
        }
return 0;

}


