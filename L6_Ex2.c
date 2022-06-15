#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();
#include <time.h>
#define N 5 // N=cars
void* func1(void* argc);
sem_t cars[5];
int main (int argc , char* argv[])
{
	int i,place[5];
	srand(time(NULL));
    pthread_t threads[N];
	sem_t cars[N];
    for(i=0;i<N;i++)
    {
		place[i]=i;
        sem_init( &cars[i],0, 1 );
    }
	for(i=0;i<2;i++)
		 pthread_create(&threads[i],NULL,func1,(void*)&place[i]);

	sleep(3);

	return 0;
   
}
void* func1(void* argc)
{
	int num;
	int car;
    while(1)
    {
		
		num = *((int*)argc);
		printf("%d\n",num);
		sem_wait(&cars[num]); // stop the car
		car = (rand() % N);
		printf("%d\n",car);
		sem_wait(&cars[car]); // check if the random car is free
		printf("Crash\n");
		sem_post(&cars[num]);
		sem_post(&cars[car]);
    }
}