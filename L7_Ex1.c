#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, void* argv[])
{
	if(argc<2)
	{
		printf("ERROR - missing parameters\n");
		return -1;
	}
	int bytes, pid;
	char buffer[2048];
	int fdarr[2];
	if(pipe(fdarr) == -1)
	{
		printf("Error: Pipe creation failed " );
		return(-1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (close(fdarr[0]) == -1)
		{
			printf("Error: close fd failed");
			return(-1);
		}
		if( write(fdarr[1],argv[1],strlen(argv[1]))== -1 )
		{
			printf("Error: write to the pipe failed");
			return(-1);
		}
	}
	else
	{
		if (close(fdarr[1]) == -1)
		{
			printf("Error: close fd failed");
			return(-1);
		}
		if( (bytes=read(fdarr[0], buffer, 2048)) == -1 )
		{
			printf("Error: read from the pipe failed");
			return(-1);
		}
		buffer[bytes] = '\0';
		printf("%s\n", buffer);
	}
	return(0);
}