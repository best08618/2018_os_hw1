#include "header.h"

int main(int argc, char *argv[])
{
	
	while(1) {
		execSiSH();
		token();
		if(tok[0][0] =='$'){
			print_env();
		}
		else {
			tok_path();
			int copy_pathnum=tok_path();
			if(no_full(copy_pathnum)==0){
				fork_exec();
			}
		}
	}
	return 0;
}

