#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node

struct Node {
    Node * left;
    Node * right;
    int value;
};

Node * insertBST(Node * root, int value) {
    if (root == NULL) return createNode(value);
    if (root->value < value) {
        // go right
        root->right = insertBST(root->right);
    }
}