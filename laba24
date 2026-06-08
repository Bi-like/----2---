#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char type;
    char var;
    double num;
    char op;
    struct Node* left;
    struct Node* right;
} Node;

Node* createVarNode(char var) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = 'v';
    node->var = var;
    node->left = node->right = NULL;
    return node;
}

Node* createNumNode(double num) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = 'n';
    node->num = num;
    node->left = node->right = NULL;
    return node;
}

Node* createOpNode(char op, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = 'o';
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

Node* buildTree(char* expr) {
    Node* stack[100];
    char ops[100];
    int top = -1, optop = -1;

    for (int i = 0; expr[i]; i++) {
        if (isspace(expr[i])) continue;

        if (isalpha(expr[i])) {
            stack[++top] = createVarNode(expr[i]);
        } else if (isdigit(expr[i]) || expr[i] == '.') {
            char numStr[50];
            int j = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                numStr[j++] = expr[i++];
            }
            numStr[j] = '\0';
            i--;
            double num = atof(numStr);
            stack[++top] = createNumNode(num);
        } else if (expr[i] == '(') {
            ops[++optop] = expr[i];
        } else if (expr[i] == ')') {
            while (optop >= 0 && ops[optop] != '(') {
                char op = ops[optop--];
                Node* right = stack[top--];
                Node* left = stack[top--];
                stack[++top] = createOpNode(op, left, right);
            }
            optop--;
        } else if (isOperator(expr[i])) {
            while (optop >= 0 && ops[optop] != '(' && precedence(ops[optop]) >= precedence(expr[i])) {
                char op = ops[optop--];
                Node* right = stack[top--];
                Node* left = stack[top--];
                stack[++top] = createOpNode(op, left, right);
            }
            ops[++optop] = expr[i];
        }
    }

    while (optop >= 0) {
        char op = ops[optop--];
        Node* right = stack[top--];
        Node* left = stack[top--];
        stack[++top] = createOpNode(op, left, right);
    }

    return stack[top];
}

int isSum(Node* node) {
    if (node == NULL) return 0;
    return node->type == 'o' && node->op == '+';
}

int isVar(Node* node) {
    if (node == NULL) return 0;
    return node->type == 'v';
}

int isMul(Node* node) {
    if (node == NULL) return 0;
    return node->type == 'o' && node->op == '*';
}

Node* copyTree(Node* root) {
    if (root == NULL) return NULL;
    if (root->type == 'v') return createVarNode(root->var);
    if (root->type == 'n') return createNumNode(root->num);
    return createOpNode(root->op, copyTree(root->left), copyTree(root->right));
}

int isVarOrNum(Node* node) {
    return node != NULL && (node->type == 'v' || node->type == 'n');
}

Node* transformMulBySum(Node* root, int* changed) {
    if (root == NULL) return NULL;

    if (isMul(root)) {
        Node* left = root->left;
        Node* right = root->right;

        if (isVarOrNum(left) && isSum(right)) {
            *changed = 1;
            Node* sum = right;
            Node* leftPart = createOpNode('*', copyTree(left), copyTree(sum->left));
            Node* rightPart = createOpNode('*', copyTree(left), copyTree(sum->right));
            return createOpNode('+', leftPart, rightPart);
        }

        if (isSum(left) && isVarOrNum(right)) {
            *changed = 1;
            Node* sum = left;
            Node* leftPart = createOpNode('*', copyTree(sum->left), copyTree(right));
            Node* rightPart = createOpNode('*', copyTree(sum->right), copyTree(right));
            return createOpNode('+', leftPart, rightPart);
        }
    }

    root->left = transformMulBySum(root->left, changed);
    root->right = transformMulBySum(root->right, changed);
    return root;
}

void treeToExpr(Node* root, char* buffer, int* pos) {
    if (root == NULL) return;

    if (root->type == 'v') {
        buffer[(*pos)++] = root->var;
    } else if (root->type == 'n') {
        char num[50];
        sprintf(num, "%g", root->num);
        for (int i = 0; num[i]; i++) buffer[(*pos)++] = num[i];
    } else if (root->type == 'o') {
        int needParen = 0;
        if (root->op == '+' || root->op == '-') {
            if (root->left && root->left->type == 'o' && (root->left->op == '*' || root->left->op == '/')) {
                needParen = 1;
            }
        }
        if (needParen) buffer[(*pos)++] = '(';
        treeToExpr(root->left, buffer, pos);
        if (needParen) buffer[(*pos)++] = ')';

        buffer[(*pos)++] = root->op;

        needParen = 0;
        if (root->op == '*' || root->op == '/') {
            if (root->right && root->right->type == 'o' && (root->right->op == '+' || root->right->op == '-')) {
                needParen = 1;
            }
        } else if (root->op == '-') {
            if (root->right && root->right->type == 'o' && (root->right->op == '+' || root->right->op == '-')) {
                needParen = 1;
            }
        }
        if (needParen) buffer[(*pos)++] = '(';
        treeToExpr(root->right, buffer, pos);
        if (needParen) buffer[(*pos)++] = ')';
    }
}

void printTree(Node* root, int depth) {
    if (root == NULL) return;
    printTree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    if (root->type == 'v') printf("%c\n", root->var);
    else if (root->type == 'n') printf("%g\n", root->num);
    else printf("%c\n", root->op);
    printTree(root->left, depth + 1);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char expr[500];
    char result[500];

    printf("=== LR24 Task 9: Variable * Sum -> Sum of Products ===\n\n");

    char testCases[][100] = {
        "a*(b+c)",
        "(x+y)*z",
        "a*(b+c)+(d*e)",
        "(p+q)*r+s*(t+u)",
        "5*(a+b)",
        "(a+b)*3",
        "a*b*c",
        "m*(n+k)+(x+y)*z"
    };
    int numTests = 8;

    for (int t = 0; t < numTests; t++) {
        strcpy(expr, testCases[t]);

        printf("=== Test %d ===\n", t + 1);
        printf("Original: %s\n", expr);

        Node* root = buildTree(expr);

        printf("\nTree (original):\n");
        printTree(root, 0);

        int changed = 0;
        Node* transformed = transformMulBySum(root, &changed);

        if (changed) {
            int pos = 0;
            treeToExpr(transformed, result, &pos);
            result[pos] = '\0';
            printf("\nTransformed: %s\n", result);
            printf("\nTree (transformed):\n");
            printTree(transformed, 0);
            freeTree(transformed);
        } else {
            printf("\nNo transformation applied.\n");
            freeTree(transformed);
        }

        freeTree(root);
        printf("\n----------------------------------------\n\n");
    }

    printf("\n=== Interactive mode ===\n");
    printf("Enter expression (or 'exit' to quit):\n");

    while (1) {
        printf("> ");
        fgets(expr, sizeof(expr), stdin);
        expr[strcspn(expr, "\n")] = '\0';

        if (strcmp(expr, "exit") == 0) break;
        if (strlen(expr) == 0) continue;

        Node* root = buildTree(expr);
        printf("\nOriginal tree:\n");
        printTree(root, 0);

        int changed = 0;
        Node* transformed = transformMulBySum(root, &changed);

        if (changed) {
            int pos = 0;
            treeToExpr(transformed, result, &pos);
            result[pos] = '\0';
            printf("\nTransformed expression: %s\n", result);
            printf("\nTransformed tree:\n");
            printTree(transformed, 0);
            freeTree(transformed);
        } else {
            printf("\nNo transformation applied (no variable * sum pattern found).\n");
            freeTree(transformed);
        }

        freeTree(root);
        printf("\n");
    }

    return 0;
}