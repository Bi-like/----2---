#include "merge.h"
#include <stdio.h>
#include <stdlib.h>

Stack* createStack(int capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (int*)malloc(sizeof(int) * capacity);
    s->top = -1;
    s->capacity = capacity;
    return s;
}

void destroyStack(Stack* s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

int isFull(Stack* s) {
    return s->top == s->capacity - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[(s->top)--];
}

void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (top to bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

Stack* mergeSortedStacks(Stack* a, Stack* b) {
    Stack* result = createStack(a->capacity + b->capacity);

    int* tempA = (int*)malloc(sizeof(int) * (a->top + 1));
    int* tempB = (int*)malloc(sizeof(int) * (b->top + 1));

    for (int i = a->top; i >= 0; i--) {
        tempA[i] = a->data[i];
    }
    for (int i = b->top; i >= 0; i--) {
        tempB[i] = b->data[i];
    }

    int i = 0, j = 0;
    while (i <= a->top && j <= b->top) {
        if (tempA[i] <= tempB[j]) {
            push(result, tempA[i++]);
        } else {
            push(result, tempB[j++]);
        }
    }

    while (i <= a->top) push(result, tempA[i++]);
    while (j <= b->top) push(result, tempB[j++]);

    free(tempA);
    free(tempB);
    return result;
}