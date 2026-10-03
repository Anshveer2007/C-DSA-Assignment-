#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5

typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

bool isEmpty(CircularQueue *q) {
    return q->front == -1;
}

void enqueue(CircularQueue *q, int x) {
    if (isFull(q)) {
        printf("[ERROR] Queue Overflow! Cannot insert %d.\n", x);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    q->arr[q->rear] = x;
    printf("[SUCCESS] Enqueued %d.\n", x);
}

int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("[ERROR] Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    printf("[SUCCESS] Dequeued %d.\n", value);
    return value;
}

int getFront(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("[ERROR] Queue is empty.\n");
        return -1;
    }
    return q->arr[q->front];
}

void display(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("[INFO] Queue is empty.\n");
        return;
    }
    printf("Current Queue (Front to Rear): ");
    int i = q->front;
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    CircularQueue q;
    initQueue(&q);

    printf("--- Circular Queue Demonstration ---\n\n");
    dequeue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60); // Overflow test
    display(&q);

    dequeue(&q);
    dequeue(&q);
    display(&q);

    enqueue(&q, 60); // Circular wrap test
    display(&q);

    return 0;
}
