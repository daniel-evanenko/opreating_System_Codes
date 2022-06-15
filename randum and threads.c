#include <stdio.h>
#include <stdlib.h> // for malloc
#include <unistd.h> // for sleep();
#include <pthread.h> // for threads
#include <time.h> // for rand()

void* randNum(void* arg)
{
    int *num = (int*) malloc(sizeof(int));
    *num = rand()%100+1; // numbers 0-100
    return ((void*)num);
}

int main()
{
    srand(time(NULL));
    void* ans;
    int i,result=0;
    pthread_t threads[5];
    for(i=0;i<5;i++) // create five threads calling the randomNum func
        pthread_create(&threads[i],NULL,randNum,NULL);
    for(i=0;i<5;i++)
    {
        pthread_join(threads[i],&ans); // returns the addres of ans
        result+=*((int*)ans); // storing the value of ans (the randumNumber) of evrey trhead into result
    }
    printf("the sum of all randum numbers = %d\n",result); // printing the sum of all randum numbers
    return 0;
}
