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
    int shmid;
    pid_t child;
    shmid = shmget((key_t)1122,4096,IPC_CREAT | 0666);
    ptr = shmat(shmid,NULL,0666);
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
        execlp("./shmgetfibc","./shmgetfibc",argv[1],NULL);
    }
    else{
        wait(NULL);
        printf("[Parent] Child completed\n");
        printf("Parent printing\n");
        printf("%s",(char *)ptr);
        shmdt(ptr);
        shmctl(shmid,IPC_RMID,NULL);
    }
    return 0;
}