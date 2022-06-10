#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread1() {
	printf("Hello thred1\n");
}

void* thread2() {
        printf("Hello thred2\n");
}
int main(){

	pthread_t thread_id1 , thread_id2;
	printf("Before \n");

	int ret1 = pthread_create( &thread_id1, NULL, thread1, NULL);
	int ret2 = pthread_create( &thread_id2, NULL, thread2, NULL);

	printf("After \n");

	/* Wait till threads are complete before main continues. Unless we  */
        /* wait we run the risk of executing an exit which will terminate   */
        /* the process and all threads before the threads have completed.   */


	pthread_join( thread_id1, NULL);
        pthread_join( thread_id2, NULL);

	printf("Thread 1 returns: %d\n",ret1);
	printf("Thread 2 returns: %d\n",ret2);



	return 0;
}
