#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

// Structure for message queue
struct msg_buffer {
    long msg_type;
    char msg_text[MAX];
} message;

int main() {
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok("progfile", 65);

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Step 1: Send message
    message.msg_type = 1;
    strcpy(message.msg_text, "Are you hearing me?");
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Process 1: Sent -> %s\n", message.msg_text);

    // Step 2: Receive reply
    msgrcv(msgid, &message, sizeof(message), 2, 0);
    printf("Process 1: Received -> %s\n", message.msg_text);

    // Step 3: Send final message
    message.msg_type = 1;
    strcpy(message.msg_text, "I can hear you too.");
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Process 1: Sent -> %s\n", message.msg_text);

    return 0;
}
