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
