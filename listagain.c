#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct List List;

struct Node {
    Node * nxt, * prv;
    int data;
};

struct List {
    Node * head, * tail;
};

void removeHead (List * lst) {
    if (lst == NULL || lst->head == NULL) 
        return;


    // 1 node case check
    if (lst->head == lst->tail) {
        free(lst->head);
        lst->head = lst->tail = NULL;
        return;
    }

    lst->head = lst->head->nxt;
    free(lst->head->prv); // remove old head
    lst->head->prv = NULL; // Nothing is before head
}

void removeTail(List * lst) {
    if (lst == NULL || lst->head == NULL) 
        return;


    // 1 node case check
    if (lst->head == lst->tail) {
        free(lst->tail);
        lst->head = lst->tail = NULL;
        return;
    }

    lst->tail = lst->tail->prv;
    free(lst->head->nxt); // remove old head
    lst->head->nxt = NULL; // Nothing is before head
}

Node * createNode(int data) {
    Node * res = (Node *) malloc(sizeof(Node));
    res->data = data;
    res->nxt = res->prv = NULL;
    return res;

}

void insertHead(List * lst, int data) {
    if (lst == NULL) return;

    // Empty list case
    if (lst->head == NULL) {
        lst->head = lst->tail = createNode(data);
        return;
    }

    // Connect the node to the list
    lst->head->prv = createNode(data);
    lst->head->prv->nxt = lst->head;

    // Point to the new head
    lst->head - lst->head->prv;
}

void insertTail(List * lst, int data) {
    if (lst == NULL) return;

    // Empty list case
    if (lst->head == NULL) {
        lst->head = lst->tail = createNode(data);
        return;
    }

    // Connect the node to the list
    lst->tail->nxt = createNode(data);
    lst->tail->nxt->prv = lst->tail;

    // Point to the new head
    lst->tail - lst->tail->nxt;
}

void printList(List * lst) {
    Node * cur = lst->head;
    while (cur != NULL) {
        printf()
    }
}

int main() {
    List lst;
    lst.head = lst.tail = NULL;

    for (int i = 0; i<10; i++) {
        if (i % 2) {
            insertTail(&lst, i);
        } else {
            insertHead(&lst, i);
        }
        

    }

    for (int i = 0; i<10; i++) {
        if (i % 2) {
            removeTail(&lst);
        } else {
            removeHead(&lst);
        }

    }

    return -;
}


