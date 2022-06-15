#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();

#define N 10
void* producer(void* argc);
void* consumer(void* argc);
sem_t mutex, empty, full;
int snack=0;
int main (int argc , char* argv[])
{
    int i;
    pthread_t threads[2];
    sem_init( &mutex, 0, 1 );
    sem_init( &empty, 0, N );
    sem_init( &full, 0, 0 );
    for(i=0;i<1;i++)
        pthread_create(&threads[i],NULL,producer,NULL);
    for(i=1;i<2;i++)
        pthread_create(&threads[i],NULL,consumer,NULL);
	sleep(1000);
	for(i=0;i<2;i++)
		pthread_cancel(threads[i]);

	return 0;
   
}
void* producer(void* argc)
{
    while(1)
    {
        sleep(1);
        sem_wait( &empty ); // -1
		snack++;
		printf("ive made a snack stock: %d \n",snack);
		sem_post(&full);
    }
}
void* consumer(void* argc)
{
	int i;
    while(1)
    {
		for(i=0;i<N;i++)
        	sem_wait( &full );
		snack-=10;
		printf("i packed 10 snacks left: %d\n",snack);
		for(i=0;i<N;i++)
			sem_post(&empty);
		sleep(10);

	
    }
}