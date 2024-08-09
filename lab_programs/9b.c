// Write a program to generate first N ODD numbers with the following
// requirements:
// - Parent program should create a child and distribute the task of generating odd numbers to its child.
// - The code for generating odd numbers should reside in different program.
// - Child should write the odd numbers to a shared memory.
// - Parent process has to print the odd numbers by retrieving from the shared memory.
// a.	Implement the above using shmget and shmat
// Note: Shared object should be removed at the end in the program

//Parent.c

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
	int n;
	int arr[100];
} pack_t;

int main() {
	key_t key = 1234;
	int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);
	pack_t* shm_ptr = (pack_t*) shmat(shmid, NULL, 0666);
	printf("[PARENT] Created shared memory with key = %d, id = %d, address = %p\n", key, shmid, shm_ptr);
	printf("[PARENT] Enter n: ");
	scanf("%d", &shm_ptr->n);
	pid_t child_pid;
	if ((child_pid = fork()) == 0) {
		execlp("./child", "./child", NULL); // Child
	} else {
		wait(NULL);
		printf("[PARENT] Child finished executing.\n");
		printf("[PARENT] The first %d odd numbers are: \n", shm_ptr->n);
		for (int i = 0; i < shm_ptr->n; i++)
			printf("%d ", shm_ptr->arr[i]);
		putchar('\n');
	}

	shmdt((void*) shm_ptr);
	shmctl(shmid, IPC_RMID, NULL); // Delete shared memory
	printf("[PARENT] Shared Memory Deleted\n");
	return 0;
}

//Child.c

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

typedef struct {
	int n;
	int arr[100];
} pack_t;

int main() {
	key_t key = 1234;
	int shmid = shmget(key, sizeof(pack_t), 0666);
	pack_t* shm_ptr = (pack_t*) shmat(shmid, NULL, 0666);
	printf("[CHILD] Attached to shared memory with key = %d, id = %d. address = %p\n", key, shmid, shm_ptr);
	for (int i = 0; i < shm_ptr->n; i++)
		shm_ptr->arr[i] = 2*i + 1;
	printf("[CHILD] Finished generating first %d odd numbers\n", shm_ptr->n);
	shmdt((void*) shm_ptr);
	return 0;
}

