#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    char command[10];
    do
    {
        printf("please enter a command ( ls / date / ps)\n");
        scanf("%s",command);
        if(strcmp(command,"q")==0)
            break;
		pid_t id=fork();
		if(id == -1)
			perror("fork");
		if(id==0)
		{
			execlp(command, command,0);
			perror("execlp");
		}
        wait();
    }while(1);
    printf("GoodBye\n");
    return 0;
}