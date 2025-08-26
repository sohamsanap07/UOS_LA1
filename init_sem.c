// init_sem.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok("init_sem.c", 'A'); // Generate unique key
    int semid = semget(key, 1, 0666 | IPC_CREAT); // Create 1 semaphore

    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    union semun u;
    u.val = 1; // initialize semaphore with value 1
    if (semctl(semid, 0, SETVAL, u) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Semaphore created with ID: %d\n", semid);
    return 0;
}
