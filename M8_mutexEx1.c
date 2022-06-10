#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

static int g=0;
pthread_mutex_t lock;

void* inc_thread() {
	while(1){
		pthread_mutex_lock(&lock);
		g++;
		printf("inc:%d\n",g);
		pthread_mutex_unlock(&lock);
	}
}

void* dec_thread() {
        while(1){
		pthread_mutex_lock(&lock);
                g--;
		printf("dec:%d\n",g);
                pthread_mutex_unlock(&lock);
	}
	
}
int main(){

	pthread_t thread_id1 , thread_id2;
	pthread_mutex_init(&lock, NULL);

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

        pthread_mutex_destroy(&lock);

	return 0;
}
