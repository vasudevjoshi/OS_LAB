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
