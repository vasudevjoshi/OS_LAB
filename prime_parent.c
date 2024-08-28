#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[]){
	int i,j;
	int shm_fd;
	void *ptr;
	if(argc > 2){
		sscanf(argv[1],"%d",&i);
		sscanf(argv[2],"%d",&j);
		if( i<2){
			printf("Error Input:\n");
			return 0;
		}
	}
	else{
		printf("No or less arguements passed in the command line:\n");
		exit(0);
	}
	pid_t child;
	child = fork();
	if(child == 0){
		execlp("./prime_child","./prime_child",argv[1],argv[2],NULL);
	}
	else{
		wait(NULL);
		printf("[PARENT] Child completed execution\n");
		shm_fd = shm_open("vasu",O_RDONLY,0666);
		ptr = mmap(0,4096,PROT_READ,MAP_SHARED,shm_fd,0);
		printf("[Parent] parent printing:\n");
		printf("%s ",(char *)ptr);
		shm_unlink("vasu");
	}
	
	return 0;
}
