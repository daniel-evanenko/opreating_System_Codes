#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();

#define N 20
void* producer(void* argc);
void* consumer(void* argc);
sem_t mutex, empty, full;
int snack=0;
int main (int argc , char* argv[])
{
    int i;
    pthread_t threads[10];
    sem_init( &mutex, 0, 1 );
    sem_init( &empty, 0, N );
    sem_init( &full, 0, 0 );
    for(i=0;i<7;i++)
        pthread_create(&threads[i],NULL,producer,NULL);
    for(i=7;i<10;i++)
        pthread_create(&threads[i],NULL,consumer,NULL);
	sleep(25);
	for(i=0;i<10;i++)
		pthread_cancel(threads[i]);

	return 0;
   
}
void* producer(void* argc)
{
    while(1)
    {
        sleep(2);
        sem_wait( &empty ); // -1
        sem_wait( &mutex ); // if there is someone eating or creating a snack -> wait?
		snack++;
		printf("ive made a snack stock: %d \n",snack);
        sem_post( &mutex ); // if the snack was created -> free the mutex and let someone else do there job
        sem_post( &full ); // if the machine full -> wait till someone ate a snack and add the new one. else -> add the new one 
    }
}
void* consumer(void* argc)
{
    while(1)
    {
        sem_wait( &full ); // take one snack from the machine. if there is noting left - > wait till someone makes one
        sem_wait( &mutex ); // if there was a snack and theres no one making or eating right now -> start eating, else -> wait till someone has finish his job.
		snack--;
		printf("i took a snack, left: %d\n",snack);
        sem_post( &mutex ); // if you ate the snack free the place for someone else
        sem_post( &empty ); // update that you took a snack
        sleep(3);
        printf("i ate a snack\n");
	
    }
}