#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

char* read_command(void);
char** tokenize(char* tok,char* line);
int count_path;

int main(void){
	printf("shell from jinhwa");
        char* path = getenv("PATH");
	char** tok_path = tokenize(":",path);
	char* line;
	char** tok_com;
	struct stat buf;
	pid_t pid;
	int count = 0; 
	while(1){
		printf(">");
		line=read_command();
		tok_com= tokenize(" ",line);
		int i;
		int ret;
		if(strncmp(tok_com[0],"quit",4)==0)
			break;
		for(i=0;i<count_path;i++){
			char* imm = malloc(sizeof(char*));
			strcat(imm,tok_path[i]);
                	strcat(imm,"/");
                	strcat(imm,tok_com[0]);
			ret = stat(imm,&buf);
			if(ret == 0){
				pid=fork();
				if(pid==0)
				{
					execve(imm,tok_com,NULL);
					break;
				}
				else if(pid == -1){
					perror("fork error");
					exit(0);
				}
				else{
					wait(0);
					break;
				}
			}
		}
		if(i>=count_path)
			printf("No such a file\n");	
	
	}

	return 0;


}

char* read_command(void)
{
        int bufsize =1024;
        int size = 0;
        char * buffer  = malloc(sizeof(char)* bufsize);
        int character;
        /*if(!buffer){
                printf("allocation error");
                exit(0);
        }*/
        while(1)
        {
                character= getchar();
                if( character == '\n'){
                        buffer[size] = '\0';
                        return buffer;
                }
                else{
                        buffer[size] = character;
                }
                size ++ ;
                if(size >= bufsize){
                        bufsize += 1024;

                }
        }

}

char** tokenize(char* tok, char* line)
{
        char** tok_command=malloc(100);
        int tok_num = 0;
        char* token = strtok(line,tok);
        tok_command[tok_num++] = token;
        while(token)
        {
                token = strtok(NULL,tok);
                tok_command[tok_num] = token;
                tok_num ++ ;

        }
	if(tok == ":")
		count_path = tok_num-1;
        return tok_command;
}





