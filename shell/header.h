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
char currLoc[255], input[40], new_tok[200];
char *tok[100], *new_token[100];
char new_path[100][100];

//struct
struct stat fstat_buf;

//function
void execSiSH();
void token();
void print_env();
int tok_path();
int no_full(int copy_pathnum);
int fork_exec();
