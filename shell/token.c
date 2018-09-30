#include "header.h"

void token(){
	int j = 0;
	char *saveptr;
	char* str;
	for (str=input; ;str= NULL,j++) {
		tok[j] = strtok_r(str, " ", &saveptr);
		if (tok[j] == NULL) {
			if (tok[0] == NULL) {
				tok[0] = "space";
			}
			break;
		}
	}
}

