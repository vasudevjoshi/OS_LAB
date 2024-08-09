// Write a program to generate and print Prime numbers between a given range
//  (between M & N) with the following requirements:- M&Nshouldbepassed as command line arguments.- Error checking should be done to verify the required number of arguments at the
//  command line.- Parent program should create a child and distribute the task of generating Prime
//  numbers to its child.- The code for generating Prime numbers should reside in different program.- Child should write the generated Prime numbers to a shared memory.- Parent process has to print by retrieving the Prime numbers from the shared memory.
//  i. Implement the above using shm _open and mmap.
//  Note: Shared object should be removed at the end in the program

// Parent.c
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

// Child.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int i, j;
    int shm_fd;
    void *ptr;
    const int SIZE = 4096;
    char buffer[SIZE];

    shm_fd = shm_open("vasu", O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    i = atoi(argv[1]);
    j = atoi(argv[2]);
    int flag;
   // int offset = 0;
    printf("CHILD\n");
    printf("The prime numbers in the given range %d and %d are:\n", i, j);
    for (int num = i; num < j; num++) {
        flag = 0;
        for (int k = 2; k <= num / 2; k++) {
            if (num % k == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            sprintf(ptr,"%d\t",num);
            ptr+=strlen(ptr);
            printf("%d\t",num);
        }
    }
printf("\n");
    return 0;
}


