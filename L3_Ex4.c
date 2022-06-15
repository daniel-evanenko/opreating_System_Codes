#include <stdio.h>
#include <unistd.h>
int main (int argc , char* argv[])
{
	if(argc<2)
	{
		printf("ERROR - missing parameters\n");
		return -1;
	}
	int i;
	
	for(i=1;i<=argc-1;i++)
	{
		pid_t id=fork();
		if(id == -1)
			perror("fork");
		if(id==0)
		{
			execv(argv[i],NULL);
			perror("execv");
		}
		wait();
	}
	return 0;
}