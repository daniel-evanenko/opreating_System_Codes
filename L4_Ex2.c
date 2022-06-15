#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();
#include <pthread.h> // for threads
#include <time.h> // for rand()
#include <fcntl.h>
#include <string.h>

void* randNum(void* arg)
{
    int *num = (int*) malloc(sizeof(int));
    *num = rand()%100+1; // numbers 1-100
    return ((void*)num);
}
int main (int argc , char* argv[])
{
	if(argc<2)
	{
		printf("ERROR - missing parameters\n");
		return -1;
	}
    srand(time(NULL));
    int N = atoi(argv[1]);
    void* ans;
    int i,result=0;
    pthread_t *threads = malloc(sizeof(pthread_t)*N); // allocate an array of pthread_t with size of the user input.
    for(i=0;i<N;i++) // create N threads calling the randomNum func
        pthread_create(&threads[i],NULL,randNum,NULL);
    for(i=0;i<N;i++)
    {
        pthread_join(threads[i],&ans); // returns the addres of ans
        result+=*((int*)ans); // storing the value of ans (the randumNumber) of evrey trhead into result
    }
    printf("the sum of all randum numbers = %d\n",result); // printing the sum of all randum numbers
    return 0;
}
