/*Write a program to implement the solution to reader-writer problem using mutex and semaphore*/
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt=1;
int numReader=0;

void *writer(void *wno){
	sem_wait(&wrt);
	cnt*=2;
	printf("Writer %d modified the count as %d\n",((int)wno),cnt); 
	sem_post(&wrt);
	return NULL;
}

void *reader(void *rno){
	pthread_mutex_lock(&mutex);
	numReader++;
	if(numReader ==1){
		sem_wait(&wrt);
	}
	pthread_mutex_unlock(&mutex);
	printf("Reader %d reads count as %d\n",((int)rno),cnt);
	pthread_mutex_lock(&mutex);
	numReader--;
	if(numReader == 0){
		sem_post(&wrt);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}


int main(){
	pthread_t r[3],w[3];
	pthread_mutex_init(&mutex,NULL);
	sem_init(&wrt,0,1);
	int ids[3]={1,2,3};
	for(int i=0;i<3;i++){
		pthread_create(&w[i],NULL,writer,&ids[i]);
	}
	for(int i=0;i<3;i++){
		pthread_create(&r[i],NULL,reader,&ids[i]);
	}
	for(int i=0;i<3;i++){
		pthread_join(r[i],NULL);
	}
	for(int i=0;i<3;i++){
		pthread_join(w[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&wrt);
	return 0;
	
}