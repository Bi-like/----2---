#ifndef MERGE_H
#define MERGE_H

typedef struct Stack {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity);
void destroyStack(Stack* s);
int isFull(Stack* s);
int isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
void printStack(Stack* s);
Stack* mergeSortedStacks(Stack* a, Stack* b);

#endif