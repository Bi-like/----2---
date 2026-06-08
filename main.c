#include "merge.h"
#include <stdio.h>

int main() {
    Stack* s1 = createStack(10);
    Stack* s2 = createStack(10);

    push(s1, 1);
    push(s1, 3);
    push(s1, 5);
    push(s1, 7);

    push(s2, 2);
    push(s2, 4);
    push(s2, 6);
    push(s2, 8);

    printf("First stack (sorted):\n");
    printStack(s1);

    printf("\nSecond stack (sorted):\n");
    printStack(s2);

    Stack* merged = mergeSortedStacks(s1, s2);

    printf("\nMerged stack (sorted ascending):\n");
    printStack(merged);

    destroyStack(s1);
    destroyStack(s2);
    destroyStack(merged);

    return 0;
}