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
    int k =2,n1,n2,n3;
    int shmid,i;
    void *ptr;
    shmid = shmget((key_t)1122,4096,0666);
    ptr = shmat(shmid,NULL,0666);
    i = atoi(argv[1]);
    n1 = 0; n2 = 1;
    sprintf(ptr,"%d ",n1);
    printf("%d ",n1);
    ptr+=strlen(ptr);
    sprintf(ptr,"%d ",n2);
    printf("%d ",n2);
    ptr+=strlen(ptr);
    while(k!=i){
        n3 = n1 + n2;
        sprintf(ptr,"%d ",n3);
        printf("%d ",n3);
        n1 =n2;
        n2 = n3;
        ptr+=strlen(ptr); 
        k++;  
    }
     shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
