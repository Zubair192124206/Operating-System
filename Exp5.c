#include <stdio.h>
#include <stdlib.h>

// Define structure for a process
typedef struct Process {
    int id;
    int priority;
} Process;

// Define structure for a priority queue node
typedef struct Node {
    Process process;
    struct Node* next;
} Node;

// Define structure for a priority queue
typedef struct {
    Node* front;
} PriorityQueue;

// Function to initialize an empty priority queue
PriorityQueue* initializePriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    return pq;
}

// Function to create a new node
Node* createNode(Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a process into the priority queue
void enqueue(PriorityQueue* pq, Process process) {
    Node* newNode = createNode(process);

    // If priority queue is empty or new process has higher priority than the front
    if (pq->front == NULL || process.priority > pq->front->process.priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        Node* current = pq->front;

        // Traverse to find the correct position to insert the new process
        while (current->next != NULL && current->next->process.priority >= process.priority) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to dequeue the process with the highest priority
Process dequeue(PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Priority Queue is empty\n");
        exit(EXIT_FAILURE);
    } else {
        Node* temp = pq->front;
        Process process = temp->process;
        pq->front = pq->front->next;
        free(temp);
        return process;
    }
}

int main() {
    // Initialize priority queue
    PriorityQueue* pq = initializePriorityQueue();

    // Example processes with priorities
    Process p1 = {1, 10};
    Process p2 = {2, 5};
    Process p3 = {3, 15};

    // Enqueue processes
    enqueue(pq, p1);
    enqueue(pq, p2);
    enqueue(pq, p3);

    // Dequeue and execute processes in order of priority
    while (pq->front != NULL) {
        Process nextProcess = dequeue(pq);
        printf("Executing process %d with priority %d\n", nextProcess.id, nextProcess.priority);
    }

    // Free memory used by the priority queue
    free(pq);

    return 0;
}

