#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int main(int argc, void* argv[])

{



	int bytes, pid;

	char buffer[2048];

	int fdarr1[2];

    int fdarr2[2];

	if(pipe(fdarr1) == -1 || pipe(fdarr2) == -1)

	{

		printf("Error: Pipe creation failed " );

		return(-1);

	}

    printf("START\n");

	pid = fork();

	if (pid == 0)

	{

        int i;

        for(i=0;i<9;i++)

        {

            char string[24] = "CHILD: message number  \n";

            char num = (i+1+'0');

            string[22] = num;

        	if( write(fdarr1[1],string,24)== -1)

		    {

			    printf("Error: write to the pipe failed");

			    return(-1);

		    }    

        }

		if( (bytes=read(fdarr1[0], buffer, 2048)) == -1 )

		{

			printf("Error: read from the pipe failed");

			return(-1);

		}

		buffer[bytes] = '\0';

		printf("%s\n", buffer);

	}

	else

	{

        

        int i;

        for(i=0;i<9;i++)

        {

            char string[25] = "FATHER: message number  \n";

            char num = (i+1+'0');

            string[23] = num;

        	if( write(fdarr2[1],string,25)== -1)

		    {

			    printf("Error: write to the pipe failed");

			    return(-1);

		    }    

        }

        if( (bytes=read(fdarr2[0], buffer, 2048)) == -1 )

		{

			printf("Error: read from the pipe failed");

			return(-1);

		}

		buffer[bytes] = '\0';

		printf("%s\n", buffer);

	}

	return(0);

}