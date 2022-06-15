#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();
#include <time.h>
#define N 5 // N=cars

void* phoneCall(void* argc);
sem_t friends [N];

int main (int argc , char* argv[])
{
	int i,place[5];
	srand(time(NULL));
    pthread_t threads[N];
    for(i=0;i<N;i++)
    {
		place[i]=i;
        sem_init( &friends[i],0, 1 );
    }
	for(i=0;i<5;i++)
	{
		 pthread_create(&threads[i],NULL,phoneCall,(void*)&place[i]);
	}

	sleep(10000);

	return 0;
   
}
void* phoneCall(void* argc)
{
	int index = *((int*)argc);
	int friend = (rand()%N);
    while(1)
    {
		
		while(index == friend)
		{
			friend = (rand()%N);
		}
	if(index>friend) // swap. so its stars with the smallest car.
	{
		int temp = index;
		index = friend;
		friend = temp;
	}
	sem_wait(&friends[index]); // stop the car
	sem_wait(&friends[friend]);
	printf("friend %d is talking with friend %d\n",index,friend);
	sleep(1);
	sem_post(&friends[friend]);
	sem_post(&friends[index]);
	friend = (rand()%N);
    }
}