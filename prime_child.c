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
    if (shm_fd == -1) {
        perror("Shared memory open failed");
        exit(1);
    }

    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Memory mapping failed");
        exit(1);
    }

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

