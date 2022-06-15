#include <semaphore.h>

#include <pthread.h>

#include <stdio.h>

#include <stdlib.h> // for malloc

#include <unistd.h> // for sleep();

void* func1(void* argc);

void* func2(void* argc);

sem_t empty, full;

int main (int argc , char* argv[])

{

    pthread_t thread1;

	pthread_t thread2;

	sem_init( &empty, 0, 1 );

	sem_init( &full, 0, 0 );



    pthread_create(&thread1,NULL,func1,NULL);

    pthread_create(&thread2,NULL,func2,NULL);

	sleep(3);

	pthread_cancel(thread1);

	pthread_cancel(thread2);



	return 0;

   

}

void* func1(void* argc)

{

	int msg1=0;

    while(1)

    {

			sem_wait( &empty );

			msg1++;

			printf("msg num: %d, im am thread number1\n",msg1);

			sem_post( &full );

    }

}



void* func2(void* argc)

{

	int msg2=0;

    while(1)

    {

			sem_wait( &full );

			msg2++;

			printf("msg num: %d, im am thread number 2\n",msg2);

			sem_post( &empty );

    }

}