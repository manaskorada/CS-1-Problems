#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19

typedef struct customer {
    char name[MAXLEN + 1];
    int points;
} customer;

typedef struct treenode {
    customer *cPtr;
    int size;
    struct treenode *left;
    struct treenode *right;
} treenode;

treenode *insert(treenode *root, customer *c) {
    if (root == NULL) {
        treenode *node = (treenode *)malloc(sizeof(treenode));
        node->cPtr = c;
        node->left = node->right = NULL;
        node->size = 1;
        return node;
    }

    if (strcmp(c->name, root->cPtr->name) < 0) {
        root->left = insert(root->left, c);
    } else if (strcmp(c->name, root->cPtr->name) > 0) {
        root->right = insert(root->right, c);
    }

    root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);

    return root;
}

customer *search(treenode *root, char *name, int *depth) {
    if (root == NULL) {
        *depth = -1;
        return NULL;
    }

    int cmp = strcmp(name, root->cPtr->name);
    if (cmp < 0) {
        return search(root->left, name, depth);
    } else if (cmp > 0) {
        return search(root->right, name, depth);
    }

    *depth = 0;
    return root->cPtr;
}

treenode *findMax(treenode *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

treenode *deleteNode(treenode *root, char *name) {
    if (root == NULL) {
        return root;
    }

    int cmp = strcmp(name, root->cPtr->name);
    if (cmp < 0) {
        root->left = deleteNode(root->left, name);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, name);
    } else {
        if (root->left == NULL) {
            treenode *temp = root->right;
            free(root->cPtr);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            treenode *temp = root->left;
            free(root->cPtr);
            free(root);
            return temp;
        }

        treenode *maxNode = findMax(root->left);
        root->cPtr = maxNode->cPtr;
        root->left = deleteNode(root->left, maxNode->cPtr->name);
    }

    root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);

    return root;
}

int countSmaller(treenode *root, char *name) {
    int count = 0;
    while (root) {
        int cmp = strcmp(name, root->cPtr->name);
        if (cmp <= 0) {
            root = root->left;
        } else {
            count += 1 + (root->left ? root->left->size : 0);
            root = root->right;
        }
    }
    return count;
}

void inOrderTraversal(treenode *root, customer *sortedCustomers, int *index) {
    if (root) {
        inOrderTraversal(root->left, sortedCustomers, index);
        sortedCustomers[(*index)++] = *(root->cPtr);
        inOrderTraversal(root->right, sortedCustomers, index);
    }
}

void merge(customer *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    customer *L = (customer *)malloc(n1 * sizeof(customer));
    customer *R = (customer *)malloc(n2 * sizeof(customer));

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].points > R[j].points || (L[i].points == R[j].points && strcmp(L[i].name, R[j].name) < 0)) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(customer *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ... (Previous code remains unchanged)

// ... (Previous code remains unchanged)

// ... (Previous code remains unchanged)

int main() {
    int n;
    scanf("%d", &n);

    treenode *root = NULL;
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
            customer *c = (customer *)malloc(sizeof(customer));
            strcpy(c->name, names[i]);
            c->points = points[i];
            root = insert(root, c);
        } else if (strcmp(commands[i], "sub") == 0) {
            int depth;
            customer *c = search(root, names[i], &depth);
            if (c) {
                c->points = c->points - points[i];
                if (c->points < 0) {
                    c->points = 0;
                }
            }
        } else if (strcmp(commands[i], "del") == 0) {
            int depth;
            customer *c = search(root, names[i], &depth);
            if (c) {
                root = deleteNode(root, names[i]);
            }
        } else if (strcmp(commands[i], "search") == 0) {
            int depth;
            customer *c = search(root, names[i], &depth);
            if (c) {
                printf("%s %d %d\n", c->name, c->points, depth);
            } else {
                printf("%s not found\n", names[i]);
            }
        } else if (strcmp(commands[i], "count_smaller") == 0) {
            int count = countSmaller(root, names[i]);
            printf("%d\n", count);
        }
    }

    // Output remaining customers after processing commands
    int numCustomers = root ? root->size : 0;
    customer *remainingCustomers = (customer *)malloc(numCustomers * sizeof(customer));
    int index = 0;
    inOrderTraversal(root, remainingCustomers, &index);

    for (int i = 0; i < numCustomers; i++) {
        printf("%s %d\n", remainingCustomers[i].name, remainingCustomers[i].points);
    }

    // Sort the remaining customers by points and name
    mergeSort(remainingCustomers, 0, numCustomers - 1);

    // Print the sorted remaining customers
    for (int i = 0; i < numCustomers; i++) {
        printf("%s %d\n", remainingCustomers[i].name, remainingCustomers[i].points);
    }

    // Free allocated memory
    free(remainingCustomers);

    return 0;
}

