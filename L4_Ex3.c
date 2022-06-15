#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();
#include <pthread.h> // for threads
#include <time.h> // for rand()
#include <fcntl.h>
#include <string.h>

void* randNum(void* arg)
{
	int id = pthread_self();
	printf("id: %d\n",id);

    return (0);
}
int num_Array[100];
int N;
int main (int argc , char* argv[])
{
	if(argc<2)
	{
		printf("ERROR - missing parameters\n");
		return -1;
	}

    srand(time(NULL));
    N = atoi(argv[1]); // amount of threads
    void* ans; 
    int i,j,result=0;
    int thread_Ids[N];
    pthread_t *threads = malloc(sizeof(pthread_t)*N); // allocate an array of pthread_t with size of the user input.
    for(i=0;i<N;i++) // create N threads calling the randomNum func
    {
        pthread_create(&threads[i],NULL,randNum,((void*)&num_Array[i]));
        thread_Ids[i]=pthread_self();

    }

// 1 = 0-19. 2 = 19-39. 3 = 39-59; 4 = 59-79; 5 = 79-99;
    for(i=0;i<N;i++)
        pthread_join(threads[i], NULL);
    return 0;
}