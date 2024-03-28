#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h> // Include sys/wait.h for wait() function
#include <string.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key;
    char *shmaddr;

    // Generate a key for shared memory
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write a message to the shared memory
    sprintf(shmaddr, "Hello, shared memory!");

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {  // Child process
        printf("Child process reading from shared memory: %s\n", shmaddr);
        // Modify the message in shared memory
        sprintf(shmaddr, "Hi, this is the child process!");
        exit(0);
    } else {  // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent process reading from shared memory: %s\n", shmaddr);
    }

    // Detach the shared memory segment from the process's address space
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Delete the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}

