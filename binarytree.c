#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* create() {
    struct node* newnode;
    int x;

    newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Enter the data (-1 for no node): ");
    scanf("%d", &x);

    if (x == -1) {
        free(newnode);  // Free the allocated memory if no node is created
        return NULL;
    }

    newnode->data = x;

    printf("Enter left child of %d\n", x);
    newnode->left = create();

    printf("Enter right child of %d\n", x);
    newnode->right = create();

    return newnode;
}

int main() {
    struct node *root;
    root = create();

    // To verify the tree, you can write a function to print the tree (e.g., in-order traversal)
    // and call it here

    return 0;
}