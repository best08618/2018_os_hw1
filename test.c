#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
	char * test [100];
	test[0]=(char*)malloc(sizeof(char)*100);
	strcpy(test[0],"hello");
	strcat(test[0],"/");
	printf("%s",test[0]);
}
