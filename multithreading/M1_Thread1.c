#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread1() {
	printf("Hello thred1\n");
}

int main(){

	pthread_t thread_id1;
	printf("Before \n");

	int ret = pthread_create( &thread_id1, NULL, thread1, NULL);

	printf("After \n");

	/* Wait till threads are complete before main continues. Unless we  */
        /* wait we run the risk of executing an exit which will terminate   */
        /* the process and all threads before the threads have completed.   */


	pthread_join( thread_id1, NULL); 

	printf("Thread 1 returns: %d\n",ret);



	return 0;
}
