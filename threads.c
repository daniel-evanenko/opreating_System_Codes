#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
int N,K,*numbers;
void* randNum (void* index)
{
	int num,start;
	num = *((int*)index);
	for (start=num;start<=N;start+=K) // start equals to the number of the thread , and jumps K places 
		numbers[start-1] = (rand()%1000+1*num); 
		
}
int main (int argc, char*argv[])
{
	srand(time(NULL));
	int i,*place;
	pthread_t * tArr;
	if (argc !=3)
	{
		printf("ERROR - Enter 2 Numbers\n");
		exit(-1);
	}
	N = atoi(argv[1]);
	K = atoi(argv[2]);

	tArr = (pthread_t*) malloc (K*sizeof(pthread_t)); // array of K threads
	place = (int*) malloc (K*sizeof(int)); // array of K threads
	numbers = (int*) malloc (N*sizeof(int)); // array of N numbers
	if (tArr == NULL || place == NULL || numbers == NULL)
        {
			printf("Error: out of memory, allocation failed!\n");
            exit(-1);
		}
	for (i=0; i<K; i++)
	{
		place[i] = i+1;
		if(pthread_create(&tArr[i],NULL,randNum,(void*)&place[i])) // threads from 1-K
		{
			perror("pthread_create\n"); // prints the error
			exit(-1);
		}
	}
	for (i=0; i<K; i++)
	{	
		if(pthread_join(tArr[i],NULL)) // wait to all threads to finish
		{
			perror("pthread_join\n");
			exit(-1);
		}
	}
	printf("the array of random numbers: ");
	for(i=0;i<N;i++)
		printf("%d ",numbers[i]); // print the array
	printf("\n");
	// free all the alocated arrays/vars
	free(tArr);
	free(place);
	free(numbers);
	return 0;
}