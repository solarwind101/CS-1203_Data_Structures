#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Structure for a node in the stack
struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

// Structure for the stack
struct Stack {
    struct StackNode* top;
};

// Function to create a new binary tree node
struct TreeNode* createTreeNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to push a node onto the stack
void push(struct Stack* stack, struct TreeNode* data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a node from the stack
struct TreeNode* pop(struct Stack* stack) {
    if (stack->top == NULL) {
        return NULL; // Stack is empty
    }
    struct StackNode* temp = stack->top;
    struct TreeNode* data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Function for inorder traversal of the binary tree
void inorderTraversal(struct TreeNode* root) {
    struct Stack* stack = createStack();
    struct TreeNode* current = root;

    while (current != NULL || stack->top != NULL) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        current = pop(stack);
        printf("%d ", current->key);

        current = current->right;
    }

    free(stack);
}

int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(48);
    root->left = createTreeNode(32);
    root->right = createTreeNode(71);
    root->left->left = createTreeNode(22);
    root->left->right = createTreeNode(41);
    root->right->left = createTreeNode(61);
    root->right->right = createTreeNode(83);

    // Perform inorder traversal and print the result
    printf("Inorder traversal: ");
    inorderTraversal(root);

    return 0;
}

