Program no. 1

# Fixed-Size Stack Implementation in C

This repository contains a complete implementation of a **Fixed-Size Stack** data structure using a dynamic/static array in standard C without relying on built-in libraries. It handles edge cases including **Stack Overflow** and **Stack Underflow**, accompanied by space/time complexity analysis and theoretical discussions.

---

## 1. Problem Statement

Design and implement a stack using an array without built-in stack libraries. The program performs the following core operations:

* **`PUSH(x)`**: Pushes an integer element `x` onto the top of the stack.
* **`POP()`**: Removes and returns the top element from the stack.
* **`PEEK()`**: Returns the top element without removing it.
* **`DISPLAY()`**: Prints all elements currently in the stack from top to bottom.

The implementation handles both boundary conditions:
1. **Stack Overflow**: Attempting to push an element when the stack array is at full capacity.
2. **Stack Underflow**: Attempting to pop or peek when the stack contains no elements.

---

## 2. C Implementation Code

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CAPACITY 5

typedef struct {
    int arr[MAX_CAPACITY];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is full
bool isFull(Stack *s) {
    return s->top == MAX_CAPACITY - 1;
}

// Check if stack is empty
bool isEmpty(Stack *s) {
    return s->top == -1;
}

// PUSH operation
void push(Stack *s, int x) {
    if (isFull(s)) {
        printf("[ERROR] Stack Overflow! Cannot push %d. Stack is full.\n", x);
        return;
    }
    s->top++;
    s->arr[s->top] = x;
    printf("[SUCCESS] Pushed %d onto the stack.\n", x);
}

// POP operation
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("[ERROR] Stack Underflow! Cannot pop from an empty stack.\n");
        return -1;
    }
    int poppedValue = s->arr[s->top];
    s->top--;
    printf("[SUCCESS] Popped %d from the stack.\n", poppedValue);
    return poppedValue;
}

// PEEK operation
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("[ERROR] Stack Underflow! Stack is empty.\n");
        return -1;
    }
    return s->arr[s->top];
}

// DISPLAY operation
void display(Stack *s) {
    if (isEmpty(s)) {
        printf("[INFO] Stack is empty.\n");
        return;
    }
    printf("Current Stack (Top to Bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    initStack(&s);

    printf("--- Stack Operations Demo ---\n\n");

    // Testing Underflow
    pop(&s);
    peek(&s);
    display(&s);
    printf("\n");

    // Testing Normal Push
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);
    push(&s, 50);
    display(&s);
    printf("\n");

    // Testing Overflow
    push(&s, 60);
    printf("\n");

    // Testing Peek
    printf("Top Element (Peek): %d\n\n", peek(&s));

    // Testing Pop
    pop(&s);
    display(&s);

    return 0;
}
---

## 3. Complexity Analysis
Time Complexity
PUSH(x): O(1)
Reason: Pushing an element involves checking if the stack is full, incrementing the top pointer, and assigning the value directly to arr[top]. This takes constant time.
POP(): O(1)
Reason: Popping an element involves checking if the stack is empty, reading the value at arr[top], and decrementing the top pointer. This takes constant time.
PEEK(): O(1)
Reason: Peeking accesses the top element directly using arr[top] without modifying pointers or traversing the array. This takes constant time.
DISPLAY(): O(n)
Reason: Displaying the stack requires a linear traversal from index top down to index 0, where n is the current number of elements in the stack.
Space Complexity
Auxiliary Space Complexity: O(1)
Reason: Each individual operation (push, pop, peek, display) requires no extra memory beyond a few temporary variables.
Total Space Complexity: O(N)
Reason: Space is allocated for a fixed-size array of capacity N (where N = MAX_CAPACITY) at the start of execution.

---

## 4. Theoretical Discussion: Fixed-Size Stack Behavior
### A. Stack Overflow Mechanics
In an array-based implementation, memory is pre-allocated with a static capacity $N$. A pointer variable `top` tracks the index of the uppermost item.

* **Full Condition**: `top == N - 1`
* **Triggering Overflow**: Inserting an item when `top == N - 1` attempts to access index $N$, exceeding array bounds.

### B. Consequences of Unchecked Insertions
If boundary validation (`isFull()`) is omitted in code:
1. **Out-of-Bounds Memory Write**: Data is written outside allocated array memory bounds.
2. **Data Corruption**: Overwrites memory locations belonging to other active variables or process metadata.
3. **Runtime Crashing**: Triggers an operating system memory access violation (**Segmentation Fault / Core Dump**).

### C. Solutions to Fixed-Size Constraints
To remove hard capacity limits:
1. **Dynamic Array Rescaling**: Use memory reallocation (`realloc()`) to double array capacity dynamically when full.
2. **Linked-List-Based Stack**: Allocate stack elements dynamically as node pointers on the heap, allowing growth until available system memory is exhausted.


Program no. 2

 # Circular Queue Implementation in C

This repository contains a complete implementation of a **Circular Queue** data structure using a fixed-size array in standard C without relying on built-in queue libraries[span_2](start_span)[span_2](end_span). It correctly distinguishes between full and empty queue states and includes performance analysis along with theoretical comparisons to linear queues[span_3](start_span)[span_3](end_span)[span_4](start_span)[span_4](end_span).

---

## 1. Problem Statement

Design and implement a Circular Queue using an array in C that supports the following core operations[span_5](start_span)[span_5](end_span):

* **`ENQUEUE(x)`**: Inserts element `x` at the rear of the queue[span_6](start_span)[span_6](end_span).
* **`DEQUEUE()`**: Removes and returns the element at the front of the queue[span_7](start_span)[span_7](end_span).
* **`FRONT()`**: Returns the front element without removing it[span_8](start_span)[span_8](end_span).
* **`DISPLAY()`**: Outputs all current elements in the queue from front to rear[span_9](start_span)[span_9](end_span).

The implementation must correctly distinguish between a **Full Queue** (`isFull`) and an **Empty Queue** (`isEmpty`)[span_10](start_span)[span_10](end_span).

---

## 2. C Implementation Code

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5

typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

// Initialize queue
void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is full
bool isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// Check if queue is empty
bool isEmpty(CircularQueue *q) {
    return q->front == -1;
}

// ENQUEUE operation
void enqueue(CircularQueue *q, int x) {
    if (isFull(q)) {
        printf("[ERROR] Queue Overflow! Cannot insert %d. Queue is full.\n", x);
        return;
    }
    
    // First element insertion
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    
    q->arr[q->rear] = x;
    printf("[SUCCESS] Enqueued %d into the queue.\n", x);
}

// DEQUEUE operation
int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("[ERROR] Queue Underflow! Cannot dequeue from an empty queue.\n");
        return -1;
    }
    
    int value = q->arr[q->front];
    
    // Reset queue if only one element was left
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    
    printf("[SUCCESS] Dequeued %d from the queue.\n", value);
    return value;
}

// FRONT operation
int getFront(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("[ERROR] Queue is empty! No front element.\n");
        return -1;
    }
    return q->arr[q->front];
}

// DISPLAY operation
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

    // 1. Testing Underflow
    dequeue(&q);
    getFront(&q);
    display(&q);
    printf("\n");

    // 2. Testing Enqueue
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    display(&q);
    printf("\n");

    // 3. Testing Overflow
    enqueue(&q, 60);
    printf("\n");

    // 4. Testing Dequeue & Circular Wrap-Around
    dequeue(&q);
    dequeue(&q);
    display(&q);
    printf("\n");

    enqueue(&q, 60);
    enqueue(&q, 70);
    display(&q);
    printf("\n");

    // 5. Testing Front
    printf("Front Element: %d\n", getFront(&q));

    return 0;
}
3. Complexity Analysis

OperationTime ComplexityAuxiliary SpaceExplanation
ENQUEUE(x)\mathcal{O}(1)\mathcal{O}(1)Updates rear pointer using modulo arithmetic and writes element directly.

DEQUEUE()\mathcal{O}(1)\mathcal{O}(1)Reads index front and updates front pointer using modulo arithmetic directly.

FRONT()\mathcal{O}(1)\mathcal{O}(1)Direct array lookup at index arr[front].

DISPLAY()\mathcal{O}(n)\mathcal{O}(1)Iterates linearly over current n active elements to display them.

4. Theoretical Discussion: Circular vs. Linear Queue Behavior

A. Memory Utilization Mechanics
In a linear queue, elements are inserted at rear and deleted from front. As elements are dequeued, vacant space is created at the beginning of the array. However, because rear only moves forward, these empty slots cannot be reused once rear reaches MAX_SIZE - 1.

A Circular Queue connects the last position back to index 0 using modulo arithmetic ((rear + 1) % MAX_SIZE). This allows newly vacated front positions to be reused seamlessly for new insertions, ensuring 100% memory utilization.

B. False Overflow Issue in Linear Queues
When rear reaches the last array index (MAX_SIZE - 1) in a simple linear queue, any subsequent call to ENQUEUE() triggers a Queue Overflow error.
The Problem: This overflow error occurs even if multiple DEQUEUE() operations have freed up slots at the beginning of the array. This situation is known as False Overflow (or Memory Wastage).
The Solution: Circular queues eliminate False Overflow by wrapping indices modulo MAX_SIZE, allowing new items to occupy vacant slots at index 0 automatically.
