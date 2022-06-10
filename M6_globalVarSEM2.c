#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>
#include <stdlib.h>

static int g=0;
sem_t s1, s2;

void* inc_thread() {
	while(1){
		sem_wait(&s1);
		g++;
		printf("inc:%d\n",g);
		sem_post(&s2);
	}
}

void* dec_thread() {
        while(1){
		sem_wait(&s2);
                g--;
		printf("dec:%d\n",g);
                sem_post(&s1);
	}
	
}
int main(){

	pthread_t thread_id1 , thread_id2;
	sem_init(&s1, 0 ,0);
	sem_init(&s2, 0 ,1);

	printf("Before \n");

	int ret1 = pthread_create( &thread_id1, NULL, inc_thread, NULL);
	int ret2 = pthread_create( &thread_id2, NULL, dec_thread, NULL);

	printf("After \n");

	/* Wait till threads are complete before main continues. Unless we  */
        /* wait we run the risk of executing an exit which will terminate   */
        /* the process and all threads before the threads have completed.   */


	pthread_join( thread_id1, NULL);
        pthread_join( thread_id2, NULL);

	printf("Thread 1 returns: %d\n",ret1);
	printf("Thread 2 returns: %d\n",ret2);

        sem_destroy(&s1);
	sem_destroy(&s2);

	return 0;
}
