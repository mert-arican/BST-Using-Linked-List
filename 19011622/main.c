//
//  main.c
//  19011622
//
//  Created by Mert Arıcan on 16.04.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Represents a node of the BST

typedef struct node {
    int value;
    int whatsLeft;
    struct node *left;
    struct node *right;
} Node;

// Stack data structure and its procedures

typedef struct stack {
    int count;
    int *items;
} Stack;

void push(Stack *self, int value) {
    self->items[self->count++] = value;
}

int pop(Stack *self) {
    return self->items[--self->count];
}

int top(Stack *self) {
    return self->items[self->count-1];
}

// function to print a BST

void printBST(Node *node) {
    if (node == NULL) { return ; }
    printf("value: %d, whatsLeft: %d\n", node->value, node->whatsLeft);
    printBST(node->left);
    printBST(node->right);
}

// creating an array of random integers

bool contains(int *array, int element, int M) {
    int i = 0;
    for (i = 0; i < M; i++) {
        if (array[i] == element) { return true; }
    }
    return false;
}

int getRandomValueBetween(int lowerBound, int upperBound) {
    return lowerBound + (rand() % (upperBound-lowerBound+1));
}

int *getArrayOfRandomIntegers(int M, int N) {
    int count = 0, i = 0;
    int *array = malloc(sizeof(int) * M);
    for (i = 0; i < M; i++) {
        int randomValue = getRandomValueBetween(1, N);
        while (contains(array, randomValue, M)) {
            randomValue = getRandomValueBetween(1, N);
        }
        array[count++] = randomValue;
    }
    return array;
}

// creates a new node for the BST

Node *createNewNode(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->whatsLeft = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Inserts a value to BST

Node *assign(Node *node, int value) {
    if (node == NULL) {
        node = createNewNode(value);
    }
    else if (value > node->value) {
        node->right = assign(node->right, value);
    }
    else if (value < node->value) {
        node->left = assign(node->left, value);
    }
    return node;
}

// Creates tree with random integers...

Node *createBinaryTree(int M, int N) {
    int i = 0;
    Node *head = NULL;
    int *randomIntegers = getArrayOfRandomIntegers(M, N);
    for (i = 0; i < M; i++) {
        head = assign(head, randomIntegers[i]);
    }
    free(randomIntegers);
    return head;
}

// Searchs for given value, returns the node if found else NULL

Node *search(Node *head, int value) {
    if (head == NULL || head->value == value) { return head; }
    else if (head->value > value) { return search(head->left, value); }
    else { return search(head->right, value); }
}

// Function to print stack

void printStack(Stack *stack, int M) {
    int i = 0;
    while (i < stack->count) {
        printf("%d-", stack->items[i++]);
    }
    printf("\n");
}

// returns most left child

Node *getClosestMinNode(Node *root) {
    Node *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// deletes node from BST
Node *delete(Node *root, int value) {
    Node *node = search(root, value);
    if (node == NULL) { return root; }
    
    if (value < root->value) {
        root->left = delete(root->left, value);
    }
    
    else if (value > root->value) {
        root->right = delete(root->right, value);
    }
    
    else {
        // if it is a leaf node...
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // if it has only one child...
        else if (root->right == NULL || root->left == NULL) {
            Node *tmp = root->right == NULL ? root->left : root->right;
            free(root);
            return tmp;
        }
        
        // if it has two child...
        
        Node *tmp = getClosestMinNode(root->right);
        
        root->value = tmp->value;
        root->whatsLeft = tmp->whatsLeft;
        root->right = delete(root->right, tmp->value);
    }
    return root;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int M = 1, N = 0;
    
    while (M > N) {
        printf("M: ");
        scanf("%d", &M);
        
        printf("N: ");
        scanf("%d", &N);
        
        if (M > N) {
            printf("invalid M and N values. Try again.\n");
        }
    }
    Node *head = createBinaryTree(M, N);
    
    Stack *stack = malloc(sizeof(Stack));
    stack->count = 0;
    stack->items = malloc(M * sizeof(int));
    
    printBST(head);
    
    int k = 0, p = 0;
    
    while (stack->count < M) {
        printf("k: ");
        scanf("%d", &k);
        
        printf("p: ");
        scanf("%d", &p);
        
        Node *node = search(head, k);
        if (node != NULL) {
            node->whatsLeft = node->whatsLeft - p;
            if (node -> whatsLeft <= 0) {
                push(stack, node->value);
                head = delete(head, node->value);
            }
            printBST(head);
        }
        else {
            printf("Please enter a valid k value.\n");
        }
    }
    
    printStack(stack, M);
    free(stack->items);
    free(stack);
    return 0;
}
