
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<fcntl.h>

int main(int argc,char *argv[]){
	int i;
	pid_t child;
	int k,n1,n2,n3;
	const int SIZE = 4096; 
	int shm_fd; 
	void *ptr; 
	if(argc > 1){
		sscanf(argv[1],"%d",&i);
		if(i<1){
			printf("Error Input:%d\t",i);
			return 0;
			
		}
	}
	else{
		printf("No arguments passed  in the command line:\n");
		return 0;
	}
	child = fork();
	if(child == 0){
		execlp("./fib_child","./fib_child",argv[1],NULL);
	}
	else{
		wait(NULL);
		printf("[parent] child completed:\n");
		shm_fd = shm_open("vasu",O_RDONLY,0666);
		ptr = mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);
		printf("Parent Printing:\n");
		printf("%s",(char *)ptr);
	
	}
		shm_unlink("vasu");
	return 0;
}


