#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node * next;
    int data;
};

Node * createNode(int data) {
    Node * res = (Node *) malloc(sizeof(Node));
    res->data = data;
    res->next = NULL;
    return res;
}

// Return the head of the list from every function

Node * insertHead(Node * oldHead, int data) {
    Node * newHead = createNode(data);
    newHead->next = oldHead;

    return newHead;
}

Node * insertTail(Node * oldHead, int data) {
    // BASE CASE: Node is the head and the tail
    if (oldHead == NULL) return createNode(data);

    oldHead->next = insertTail(oldHead->next, data);

    return oldHead;
}

void printList(Node * head) {
    Node * cur = head;
    while (cur) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }

    printf("NULL\n");
}

Node * removeTail(Node * oldHead) {
    // Base CASE
    if(oldHead == NULL) {
        return NULL;
    }

    // BASE CASE: Single Node
    if (oldHead->next == NULL) {
        // Remove the node
        free(oldHead);

        // Make the head be an empty list
        oldHead = NULL;
    } else {
        // Recursive Case: More than 1 node
        oldHead->next = removeTail(oldHead->next);
    }

    
    

    // The head of the list did not change
    return oldHead;

}

void cleanList(Node * head) {
    while(head) {
        head = removeTail(head);
        printList(head);
    }
}

int main() {
    Node * head;
    head = NULL; // list is empty

    for (int i = 0; i < 10; i++) {
        if (rand() % 2 == 0)
            head = insertHead(head, i);
        else
            head = insertTail(head, i);
        printList(head);
    }
}