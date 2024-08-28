#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<sys/stat.h>
int main(int argc,char *argv[]){
    void *ptr;
    int shmfd;
    shmfd = shm_open("vasu",O_CREAT | O_RDWR,0666);
    ftruncate(shmfd,0666);
    ptr = mmap(0,4096,PROT_WRITE,MAP_SHARED,shmfd,0);
    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int flag;
    printf("CHILD\n");
    printf("the prime numbers in the given range are:\n");
    for(int num = i;num<j;num++){
            flag = 0;
        for(int k = 2;k<num/2;k++){
            if(num % k == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
                sprintf(ptr,"%d ",num);
                printf("%d ",num);
                ptr+=strlen(ptr);
            }
    }
    printf("\n");
    return 0;
}