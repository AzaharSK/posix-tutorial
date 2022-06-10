#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t count;

void* car1() {
		sem_wait(&count);
		printf("Parking Car1\n");
		sleep(6);
		sem_post(&count);
}

void* car2() {
		sem_wait(&count);
                printf("Parking Car2\n");
                sleep(4);
                sem_post(&count);	
}

void* car3() {
                sem_wait(&count);
                printf("Parking Car3\n");
                sleep(2);
                sem_post(&count);
}


void* car4() {
                sem_wait(&count);
                printf("Parking Car4\n");
                sleep(0);
                sem_post(&count);
}
int main(){

	pthread_t thread_id1 ,thread_id2, thread_id3, thread_id4;
	sem_init(&count, 0 ,3); // 3-Parking slots(resouces) && 4 cars/task

	printf("Before \n");

	int ret1 = pthread_create( &thread_id1, NULL, car1, NULL);
	int ret2 = pthread_create( &thread_id2, NULL, car2, NULL);
	int ret3 = pthread_create( &thread_id3, NULL, car3, NULL);
	int ret4 = pthread_create( &thread_id4, NULL, car4, NULL);

	printf("After \n");

	/* Wait till threads are complete before main continues. Unless we  */
        /* wait we run the risk of executing an exit which will terminate   */
        /* the process and all threads before the threads have completed.   */


	pthread_join( thread_id1, NULL);
        pthread_join( thread_id2, NULL);
	pthread_join( thread_id3, NULL);
	pthread_join( thread_id4, NULL);

	printf("Thread 1 returns: %d\n",ret1);
	printf("Thread 2 returns: %d\n",ret2);
	printf("Thread 3 returns: %d\n",ret3);
	printf("Thread 4 returns: %d\n",ret4);

        sem_destroy(&count);

	return 0;
}
