/* Manas Korada
COP 3502
0002
Projector Problem
11/12/2023
*/

// Included Libraries //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defined Constants //
#define MAXLEN 19

// Structures //
typedef struct customer {
    char name[MAXLEN + 1];
    int points;
} customer;

typedef struct treenode {
    customer * cPtr;
    int size; 
    struct treenode * left;
    struct treenode * right;
} treenode;

// Functions //

treenode * createTreeNode(char * name, int points) {
    treenode * ret = (treenode *) malloc(sizeof(treenode));

    ret->cPtr = (customer *) malloc(sizeof(customer));
    strcpy(ret->cPtr->name, name);
    ret->cPtr->points = points;

    ret->size = 1;
    ret->left = NULL;
    ret->right = NULL;
    return ret;
}


treenode * add(treenode * root, char * name, int points) {
    // Base Case: empty tree
    if (root == NULL) {
        // Create the root and return it
        printf("%s %d\n", name, points);
        return createTreeNode(name, points);
    }
    // Recursive
    if (strcmp(root->cPtr->name, name) == 0) {
        // value is already in the tree (exit)
        root->cPtr->points += points;
        printf("%s %d\n", name, root->cPtr->points);
        return root;
    }
    if (strcmp(root->cPtr->name, name) > 0) {
        // Root is bigger than the value
        // the value goes into the left side of the tree
        root->left = add(root->left, name, points);
    } else {
        // Root is smaller than the value
        // The value goes into the right side (large values)
        root->right = add(root->right, name, points);
    }
    // Return original root
    root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);

    return root;
}

treenode * sub(treenode * root, char * name, int points) {
    // Base Case: empty tree
    if (root == NULL) {
        // Create the root and return it
        printf("%s not found\n", name);
        return root;
    }
    // Recursive
    if (strcmp(root->cPtr->name, name) == 0) {
        // value is already in the tree (exit)
        if (root->cPtr->points < points) {
            root->cPtr->points = 0;
            printf("%s 0\n", name);
            return root;
        }

        root->cPtr->points -= points;
        printf("%s %d\n", name, root->cPtr->points);
        return root;
    }
    if (strcmp(root->cPtr->name, name) > 0) {
        // Root is bigger than the value
        // the value goes into the left side of the tree
        root->left = sub(root->left, name, points);
    } else {
        // Root is smaller than the value
        // The value goes into the right side (large values)
        root->right = sub(root->right, name, points);
    }
    // Return original root
    return root;
}

// Delete Function Needed

treenode *findMax(treenode *node) {
    treenode *current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

treenode *deleteNode(treenode *root, char *name) {
    if (root == NULL) {
        printf("%s not found\n", name);
        return root;
    }

    if (strcmp(root->cPtr->name, name) > 0) {
        root->left = deleteNode(root->left, name);
    } else if (strcmp(root->cPtr->name, name) < 0) {
        root->right = deleteNode(root->right, name);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            printf("%s deleted\n", name);
            treenode *temp = root->right;
            free(root->cPtr);
            free(root);
            
            return temp;
        } else if (root->right == NULL) {
            printf("%s deleted\n", name);
            treenode *temp = root->left;
            free(root->cPtr);
            free(root);
            
            return temp;
        }

        // Node with two children
        treenode *maxLeft = findMax(root->left);
        strcpy(root->cPtr->name, maxLeft->cPtr->name);
        root->cPtr->points = maxLeft->cPtr->points;
        root->left = deleteNode(root->left, maxLeft->cPtr->name);
    }
    root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
    return root;
}





// Search Need to Finish
// Return 1 if the value is in the binary search tree
// Return 0 otherwise
int search(treenode * root, char * name) {
    // Base Case: Empty tree case
    if (root == NULL) {
        printf("%s not found\n", name);
        return 0;
    }
    if (strcmp(root->cPtr->name, name) == 0) {
        printf("%s %d %d\n", name, root->cPtr->points, root->size);
        return 1;
    }
    // Technically works but why???
    // return contains(root->right, value) + contains(root->left, value);
    if (strcmp(root->cPtr->name, name) < 0) {
        // the value is larger than the root
        return search(root->right, name);
    }
    // The value must be smaller than the root
    return search(root->left, name);
}

int countSmaller(treenode *root, char *name) {
    if (root == NULL) {
        printf("%s not found\n", name);
        return 0;
    }

    if (strcmp(root->cPtr->name, name) < 0) {
        return 1 + (root->left ? root->left->size : 0) + countSmaller(root->right, name);
    } else {
        return countSmaller(root->left, name);
    }
}

// Main function //
int main() {

    int n;
    scanf("%d", &n);

    treenode * root = NULL;

    char commands[n][15];
    char names[n][MAXLEN + 1];
    int points[n];

    for (int i = 0; i < n; i++) {
        scanf("%s", commands[i]);
        if (strcmp(commands[i], "add") == 0 || strcmp(commands[i], "sub") == 0) {
            scanf("%s %d", names[i], &points[i]);
        } else {
            scanf("%s", names[i]);
        }
    }

    for (int i = 0; i < n; i++) {

        if (strcmp(commands[i], "add") == 0) {

            root = add(root, names[i], points[i]);

        } else if(strcmp(commands[i], "sub") == 0) {

            root = sub(root, names[i], points[i]);

        } else if(strcmp(commands[i], "del") == 0) {
            root = deleteNode(root, names[i]);
            
        } else if(strcmp(commands[i], "search") == 0) {
            int value_exists = search(root, names[i]);
            
            
        } else if(strcmp(commands[i], "count_smaller") == 0) {
            int count = countSmaller(root, names[i]);
            printf("%d\n", count);
            
        }


    }

    return 0;
}