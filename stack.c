#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CAPACITY 5

// Structure representing the Stack
typedef struct {
    int arr[MAX_CAPACITY];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if the stack is full (Stack Overflow condition)
bool isFull(Stack *s) {
    return s->top == MAX_CAPACITY - 1;
}

// Check if the stack is empty (Stack Underflow condition)
bool isEmpty(Stack *s) {
    return s->top == -1;
}

// PUSH operation: Adds an element x to the top of the stack
void push(Stack *s, int x) {
    if (isFull(s)) {
        printf("[ERROR] Stack Overflow! Cannot push %d. Stack is full.\n", x);
        return;
    }
    s->top++;
    s->arr[s->top] = x;
    printf("[SUCCESS] Pushed %d onto the stack.\n", x);
}

// POP operation: Removes and returns the top element
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

// PEEK operation: Returns the top element without removing it
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("[ERROR] Stack Underflow! Stack is empty, no top element.\n");
        return -1;
    }
    return s->arr[s->top];
}

// DISPLAY operation: Prints all elements from top to bottom
void display(Stack *s) {
    if (isEmpty(s)) {
        printf("[INFO] Stack is empty.\n");
        return;
    }
    printf("Current Stack Elements (Top to Bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    initStack(&s);

    printf("=======================================\n");
    printf("  C Stack Implementation Demonstration  \n");
    printf("=======================================\n\n");

    // 1. Test Stack Underflow
    printf("1. Testing Stack Underflow:\n");
    pop(&s);
    peek(&s);
    display(&s);
    printf("\n");

    // 2. Test PUSH Operations
    printf("2. Pushing elements onto the stack:\n");
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);
    push(&s, 50);
    display(&s);
    printf("\n");

    // 3. Test Stack Overflow
    printf("3. Testing Stack Overflow:\n");
    push(&s, 60);
    printf("\n");

    // 4. Test PEEK Operation
    printf("4. Peeking top element:\n");
    int topVal = peek(&s);
    if (topVal != -1) {
        printf("Top element is: %d\n", topVal);
    }
    printf("\n");

    // 5. Test POP Operations
    printf("5. Popping elements:\n");
    pop(&s);
    pop(&s);
    display(&s);

    return 0;
}
