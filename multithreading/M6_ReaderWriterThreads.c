#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>
#include <stdlib.h>

char buff[100];
sem_t write_done, read_done;

void* reader_thread() {
	while(1){
		sem_wait(&write_done);
			printf("Enter Text: ");
			fgets(buff, sizeof(buff), stdin);
		sem_post(&read_done);
	}
}

void* writer_thread() {
        while(1){
                sem_wait(&read_done);
			printf("\nPrint Text: %s\n",buff);
		sem_post(&write_done);
	}
}
int main(){

	pthread_t thread_id1 , thread_id2;
	sem_init(&write_done, 0 ,1);
	sem_init(&read_done, 0 ,0);
	printf("Before \n");

	int ret1 = pthread_create( &thread_id1, NULL, reader_thread, NULL);
	int ret2 = pthread_create( &thread_id2, NULL, writer_thread, NULL);

	printf("After \n");

	/* Wait till threads are complete before main continues. Unless we  */
        /* wait we run the risk of executing an exit which will terminate   */
        /* the process and all threads before the threads have completed.   */


	pthread_join( thread_id1, NULL);
        pthread_join( thread_id2, NULL);

	printf("Thread 1 returns: %d\n",ret1);
	printf("Thread 2 returns: %d\n",ret2);

        sem_destroy(&read_done);
        sem_destroy(&write_done);

	return 0;
}
