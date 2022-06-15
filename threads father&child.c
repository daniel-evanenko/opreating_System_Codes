#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>


int main (int argc, char *argv[])
{
    if(argc<2)
	{
        printf("ERROR - Missing parameters\n");
		return -1;
	}

    int i,n;
    pid_t id;
    n = atoi(argv[1]);
    for(i=0;i<n;i++)
    {
        id = fork(); // the child creates his childern N times
		if(id == -1)
			perror("fork");
        if(id==0)
            printf("My pid is: %d, my father pid is: %d, and im number %d in the dynasty\n",getpid(),getppid(),i+1);
		else
		{
			wait(); // if is the father
			break;
		}
    }    
}
