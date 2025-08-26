#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    int pipe1[2], pipe2[2];  // pipe1: parent->child, pipe2: child->parent
    char parent_msg[] = "Hello from Parent";
    char child_msg[] = "Hello from Child";
    char buffer[100];

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) { 
    
        close(pipe1[0]); //read
        close(pipe2[1]); //write

        // Write message to child
        write(pipe1[1], parent_msg, strlen(parent_msg) + 1);
        printf("Parent sent: %s\n", parent_msg);

        // Read reply from child
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    } else {
        close(pipe1[1]); //write
        close(pipe2[0]); // read

        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        write(pipe2[1], child_msg, strlen(child_msg) + 1);
        printf("Child sent: %s\n", child_msg);

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}
