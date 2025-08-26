#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX];
} message;

int main() {
    key_t key;
    int msgid;

    // Generate same key as Process 1
    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT); //message queue created and managed inside the kernel

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Process 2: Received -> %s\n", message.msg_text);

    message.msg_type = 2;
    strcpy(message.msg_text, "Loud and Clear.");
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Process 2: Sent -> %s\n", message.msg_text);

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Process 2: Received -> %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
