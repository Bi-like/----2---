#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Znachenie %d uzhe suschestvuet v dereve.\n", value);
    }
    return root;
}

void visualize(Node* root, int depth) {
    if (root == NULL) return;
    visualize(root->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d\n", root->data);
    visualize(root->left, depth + 1);
}

Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        printf("Znachenie %d ne naideno.\n", value);
        return NULL;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int countNodesWithDegreeEqualsValue(Node* root) {
    if (root == NULL) return 0;

    int degree = 0;
    if (root->left != NULL) degree++;
    if (root->right != NULL) degree++;

    int count = (degree == root->data) ? 1 : 0;

    count += countNodesWithDegreeEqualsValue(root->left);
    count += countNodesWithDegreeEqualsValue(root->right);

    return count;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    int choice, value;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Add node\n");
        printf("2. Visualize tree\n");
        printf("3. Delete node\n");
        printf("4. Count nodes with degree equals value\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter integer value: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("\nTree visualization:\n");
                    visualize(root, 0);
                }
                break;
            case 3:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Enter value to delete: ");
                    scanf("%d", &value);
                    root = deleteNode(root, value);
                }
                break;
            case 4:
                {
                    int result = countNodesWithDegreeEqualsValue(root);
                    printf("Number of nodes with degree equals value: %d\n", result);
                }
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    freeTree(root);
    return 0;
}