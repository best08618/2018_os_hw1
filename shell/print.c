#include "header.h"

void print_env(){
	printf("%s = %s \n",tok[0]+1,getenv(tok[0]+1));
}

