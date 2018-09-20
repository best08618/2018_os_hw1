#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	struct stat fstat_buf;
	int i;
	int ret;
	if (argc == 1)
	{
		printf("usage : stat file_path ... \n");
	}
	else
	{
		for(i=0;i<argc-1;i++)
		{
			ret = stat(argv[i+1], &fstat_buf);
			if(ret == -1)
			{
				perror("stat");
			}
		}
	}


	return 0;
}
