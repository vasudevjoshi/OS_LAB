// 7 a. Write a program to generate and print Fibonacci series with the following 
// requirements: - Parent program should create a child and distribute the task of generating 
// Fibonacci series to its child. - The code for generating Fibonacci series should reside in different 
// program. - Child should write the generated Fibonacci series to a shared memory. - Parent process has to print by retrieving the Fibonacci series from the 
// shared memory. 
// i. Implement the above using shmget and shmat 
// ii. Implement the above using shm_open and mmap 
// Note: Shared object should be removed at the end in the program. 
// //using shm_open and mmap

//Parent.c//

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


// child.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
	int k = 2,n1,n2,n3;
	void *ptr;
	int shm_fd;
	shm_fd = shm_open("vasu",O_CREAT | O_RDWR,0666);
	ftruncate(shm_fd,4096);
	ptr = mmap(0,4096,PROT_WRITE,MAP_SHARED,shm_fd,0);
	printf("Child executing:\n");
	int i = atoi(argv[1]);
	n1 = 0; n2= 1;
	sprintf(ptr,"%d ",n1);
	printf("%d ",n1);
	ptr+=strlen(ptr);
	sprintf(ptr,"%d ",n2);
	printf("%d ",n2);
	ptr+=strlen(ptr);
	while(k!=i){
		n3 = n1 +n2;
		sprintf(ptr,"%d ",n3);
		printf("%d ",n3);
		ptr+=strlen(ptr);
		n1 = n2;
		n2 = n3;
		k++;
	}
	printf("\n");
	return 0;
	
}
