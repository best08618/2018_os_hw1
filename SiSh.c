#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_LINE 256

char test[100];
char* old_dir;

char* Get_PATH(int argc, char* argv[], char* command);
char** tokenize_Cmd(char* command);
int check_existence(char* tok[], char* command);
void FORK(char* fullpath, char** tokens);
void command_cd(char** tokens);
void prompt();

int main(int argc, char **argv)
{
	char** path;
	char command[MAX_LINE];
	char fullpath[MAX_LINE];
	char** tokens;
	int i, j;
	char* dir;

	path = (char **)malloc(sizeof(char *) * 2);
	//path 찾기위한 더블포인터

	printf("Simple Shell Start\n");

	*path = "./newtest4.c";
	*(path + 1) = "PATH";
	//getenv(path[1])하면 환경변수 PATH를 알수있다

	dir = getenv("HOME");
	chdir(dir);
	old_dir = dir;
	//처음 프로그램 시작 할 때는 HOME에서 시작

	while (1)
	{
		prompt(); //prompt출력

		memset(command, 0x00, MAX_LINE);
		tokens = NULL;
		fgets(command, MAX_LINE - 1, stdin); //명령어 입력

		if (strncmp(command, "quit\n", 5) == 0)
			break;
		//quit입력하면 while함수를 나가서 프로그램 종료

		tokens = tokenize_Cmd(command);
		//명령어를 token화 한다. (ls -al => tokens[0] = "ls", tokens[1] = "-al", tokens[2] = NULL)

		if (strncmp(tokens[0], "cd", 2) == 0) {
			command_cd(tokens);
			continue;
		}//cd명령어

		if (strcpy(fullpath, Get_PATH(2, path, tokens[0])) == "wrong")
			break;
		/*Get_PATH함수를 통해 해당하는 path를 찾고 fullpath를 구함 (ls => /bin/ls)
		찾지 못하였을 경우에는 wrong command임을 알리고 새 명령어 받음.
		*/

		tokens[0] = fullpath;
		//token[0]에는 입력한 명령어가 그대로 들어 있으므로 fullpath로 바꿔준다.

		FORK(fullpath, tokens);
		//fork와 exec를 실행
	}
	return 0;
}

void prompt() {
	char *user, *pwd;
	char prompt[100];
	user = getenv("USER");

	sprintf(prompt, "%s@assam:~%s$ ", user, getcwd(pwd, 100));

	printf("%s", prompt);
}

void command_cd(char** tokens) {

	char buf[100];
	if (strncmp(tokens[1], "-\n", 1) == 0) {
		chdir(old_dir);
		old_dir = getcwd(buf, 100);
	}//cd - 일 때 이전 디렉토리로 돌아감

	else
		chdir(tokens[1]); //디렉토리 변경

	printf("%s\n", getcwd(buf, 100)); //현재 디렉토리 출력

}

char** tokenize_Cmd(char* command) {
	int j = 0;
	char *str;
	static char *tok[100];
	char *saveptr;
	char* del_line_p;

	if ((del_line_p = (char*)strchr(command, '\n')) != NULL)*del_line_p = '\0';
	//명령어 입력시에 엔터를 치기때문에 마지막에 \n이 있어서 \0로 바꿔줘야 정확한 명령어를 받을수 있음

	for (j = 0, str = command; ;str = NULL, j++) {
		if (!(tok[j] = strtok_r(str, " ", &saveptr)) && j == 0) {
			tok[j] = command;
			break;
		}//명령어 tokenize

		if (tok[j] == NULL) {
			break;
		}
	}

	return tok; //tokenize를 끝낸 더블포인터를 넘겨줌
}

int check_existence(char* tok[], char* command) {
	int ret, k;
	struct stat fstat_buf;
	char* slash = "/";
	for (k = 0; tok[k] != NULL; k++) {
		sprintf(test, "%s%s%s", tok[k], slash, command);
		//path와 명령어를 합쳐서 fullpath로 만듬
		ret = stat(test, &fstat_buf);
		//존재할시에 stat()는 0을 반환

		if (ret == 0)
			return 1;//존재 할 때
	}
	return 0;//모든 path를 확인했으나 존재하지 않을때

}


char* Get_PATH(int argc, char* argv[], char* command)
{
	test[0] = '\0';
	int i, j = 0;
	char *env, *str;
	char *tok[MAX_LINE], *saveptr;

	char* slash = "/";
	char* del_line_p;

	int ret;
	str = (char *)malloc(sizeof(char *)*MAX_LINE);
	env = (char *)malloc(sizeof(char *)*MAX_LINE);

	if ((del_line_p = (char*)strchr(command, '\n')) != NULL)*del_line_p = '\0';

	if (argc == 1) {
		printf("usage: getenv env_vars ... \n");
		return "wrong";
	}
	else {
		for (i = 0; i < argc - 1; i++) {
			env = getenv(argv[i + 1]);
			for (j = 0, strcpy(str, env); ;str = NULL, j++) {
				tok[j] = strtok_r(str, ":", &saveptr);
				if (tok[j] == NULL) break;
			}
			/*포인터 변수들이기 때문에 그냥 str = env 이런식으로 하면 str값을 바꿀때
			env도 바뀌기 때문에 string값을 받고나서 그 값을 보존하면서 써야 할때는 copy를 한다.
			*/
		}//PATH tokenize
	}

	if (ret = check_existence(tok, command))
		return test;
	//존재 할 때 path와 명령어를 합쳐서 만든 fullpath를 넘겨줌.
	//test는 전역변수. check_existence에서 다룬다.

	printf("Wrong Command\n");
	return "wrong";
	//존재하지 않으면 잘못된 명령어임을 알리고 "wrong반환"
}

void FORK(char* fullpath, char** tokens) {
	pid_t pid;
	int proc_status;

	pid = fork();//자식 프로세서 생성
	if (pid == 0)
	{
		if (execve(fullpath, tokens, NULL) == -1)
		{
			printf("failure\n");
			exit(0);
		}
	}//자식 프로세서에서 exec
	if (pid > 0)
	{
		wait(&proc_status);
	}//부모 프로세서는 wait
}

