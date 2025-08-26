// signal_sem.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int main() {
    key_t key = ftok("init_sem.c", 'A');
    int semid = semget(key, 1, 0666);

    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    struct sembuf sb = {0, 1, 0}; // V operation (increment)

    printf("Performing V (signal) operation...\n");
    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }

    printf("V operation done. Semaphore incremented.\n");
    return 0;
}
