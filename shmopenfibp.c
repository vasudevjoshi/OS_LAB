#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
    int k,n1,n2,n3,i;
    void *ptr;
    int shmfd;
    pid_t child;
    if(argc>1){
        sscanf(argv[1],"%d",&i);
        if(i<1){
            printf("Invalid Input\n");
            return 0;
        }
    }
    else{
        printf("Insufficient no of input\n");
        exit(0);
    }
    child = fork();
    if(child == 0){
        execlp("./shmopenfibc","./shmopenfibc",argv[1],NULL);
    }
    else{
        wait(NULL);
        printf("\n[Parent] Child completed\n");
        shmfd = shm_open("vasu",O_RDONLY,0666);
        ptr = mmap(0,4096,PROT_READ,MAP_SHARED, shmfd,0);
        printf("Parent printing\n");
        printf("%s",(char *)ptr);
    }
    shm_unlink("vasu");
    return 0;
}