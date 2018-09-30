#include "header.h"

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

