#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 3 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 3 // Size of the buffer
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno){
	int item;
	for(int i= 0;i<MaxItems;i++){
		item = rand()%100;
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buffer[in] = item;
		printf("Reader %d: Insert an Item %d at %d\n",*((int *)pno),buffer[in],in);
		in = (in+1)%BufferSize;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}
void *consumer(void *cno){
	int item;
	for(int i= 0;i<MaxItems;i++){
		item = buffer[out];
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		printf("Consumer %d: Remove an Item %d at %d\n",*((int *)cno),buffer[out],out);
		out = (out+1)%BufferSize;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}
int main(){
	pthread_t pro[3],con[3];
	pthread_mutex_init(&mutex,NULL);
	
	sem_init(&empty,0,BufferSize);
	sem_init(&full,0,0);
	
	int arr[3] = {1,2,3};
	for(int i= 0;i<MaxItems;i++){
		pthread_create(&pro[i],NULL,(void *)producer,(void *)&arr[i]);
	}
	for(int i= 0;i<MaxItems;i++){
		pthread_create(&con[i],NULL,(void *)consumer,(void *)&arr[i]);
	}
	for(int i = 0;i<MaxItems;i++){
		pthread_join(pro[i],NULL);
	}
	for(int i = 0;i<MaxItems;i++){
		pthread_join(con[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
	
	
}


