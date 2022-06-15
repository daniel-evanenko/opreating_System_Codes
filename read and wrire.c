#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();

void* writeF(void* argc);
void* readF(void* argc);
sem_t memory, counter;
int counterNum;
int main (int argc , char* argv[])
{
    int i;
    counterNum=0;
    pthread_t threads[7];
    sem_init(&counter, 0, 1);
    sem_init(&memory, 0, 1);

    for(i=0;i<2;i++)
        pthread_create(&threads[i],NULL,writeF,NULL);
    for(i=2;i<7;i++)
        pthread_create(&threads[i],NULL,readF,NULL);
	sleep(10000);
	for(i=0;i<7;i++)
		pthread_cancel(threads[i]);

	return 0;
   
}
void* readF(void* argc)
{
	while(1)
	{
		sem_wait(&counter);
		counterNum ++;
		if(counterNum == 1 ) // if there is a reader so the the memory.
			sem_wait (&memory);
		sem_post(&counter); // if there is another reader and the memory is acupaid let him in.
		printf("read...\n");
		sleep(1);
		sem_wait(&counter); 
		counterNum--;
		if(counterNum == 0 )
			sem_post (&memory); // if there is no readers so close the memory and let someone else in.
		sem_post(&counter);
		sleep(10);
	}
}
void* writeF(void * arg)
{	
	while(1)
	{
		sem_wait (&memory); // if the memory is free - > get in and write.
		printf("write...\n",value);
		sleep(2);
		sem_post (&memory);
		sleep(5);
	}
}
