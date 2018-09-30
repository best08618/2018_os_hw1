#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include <time.h>

pid_t pid=-1;
struct stat fstat_buf;
int ret;
int i, j=0;
char *env, *str, *saveptr;
char *tok[100];
char buf[255];

int cgetenv();

int main()
{
	char command[20];
	char *input = (char*)malloc(sizeof(char)*50);
	char *argv[]={NULL,NULL,NULL,NULL,NULL};

	cgetenv();
	while(1)
	{
		getcwd(buf,255);
		env=getenv("USER");
		printf("SISH %s@assam:%s : ",env,buf);
		fgets(command,sizeof(command),stdin);
		command[strlen(command)-1]='\0';
		if(strncmp("quit",command,4)==0)
		{
			exit(0);
		}
		else if(strncmp("PWD",command,3)==0)
		{
			env = getenv("PWD");
			printf("%s\n",env);
		}
		else if(strncmp("USER",command,4)==0)
		{
			env =getenv("USER");
			printf("User name :%s\n",env);
		}
		else if(strncmp(" ",command,1)==0)
		{
			continue;
		}
		else if(strncmp("TIME",command,4)==0)
		{
			time_t timer;
			struct tm *t;
			timer = time(NULL);
			t = localtime(&timer);
			printf("Current Time : %d:%d:%d(H/M/S)\n",t->tm_hour,t->tm_min,t->tm_sec);
		}
		else if(strncmp("cd ",command,3)==0)
		{
			strtok_r(command," ",&saveptr);
			chdir(saveptr);
		}
		else
		{
			strtok_r(command," ",&saveptr);
			if((strncmp("/",command,1))!=0)
			{
				for(j=0;tok[j]!=NULL;j++)
				{
					sprintf(input,"%s/%s",tok[j],command);
					ret=stat(input,&fstat_buf);
					if(ret==0)break;
				}
			}
			else
			{
				sprintf(input, "%s",command);
				ret=stat(input, &fstat_buf);   
			}
			if(ret==-1)
			{
				printf("No such file : %s\n",command);
				continue;
			}

			pid=fork();
			if(pid==-1)
			{
				perror("fork error");
			}
			else if(pid==0)
			{
				printf("********************child pid : %d******************\n",getpid());
				char *newenviron[]={NULL};
				argv[0]=input;
				for(j=1;;j++)
				{
					argv[j]=strtok_r(saveptr," ",&saveptr);
					if(argv[j]==NULL) break;
				}
				ret=execve(input,argv,newenviron);
				if(ret==-1) printf("execve error\n");
				exit(0); 
			}
			else
			{
				wait(0);
			}
		}
	}
	return 0;
}

int cgetenv()
{
	env = getenv("PATH");
	for (j=0,str=env; ;str= NULL,j++)
	{
		tok[j] = strtok_r(str, ":", &saveptr);
		if (tok[j] == NULL) break;
	}
	return 0;
}

