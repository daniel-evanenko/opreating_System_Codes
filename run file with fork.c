#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
int main (int argc , char* argv[])
{
	if(argc<2)
	{
		printf("ERROR - missing parameters\n");
		return -1;
	}
	int fileNum;
	pid_t id;

		printf("please enter the number of the file you want to run (1-%d)\n",argc-1);
		scanf("%d",&fileNum);
	while(fileNum<argc && fileNum>0)
	{
		id = fork();
		if(id == -1)
			perror("fork");
		if (id==0)
		{
			execv(argv[fileNum],NULL);
			perror("execv");
			return 0;
		}
		else
			wait();
		printf("please enter the number of the file you want to run (1-%d)\n",argc-1);
		scanf("%d",&fileNum);
	}
	printf("Goodbye\n");
	return 0;

}
