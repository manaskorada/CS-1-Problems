#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct List List;

struct Node {
    int data;
    Node * next;

};

struct List {
    Node * head;
    Node * tail;
    int num_nodes;

};

void insertHead(List * my_list, int data) {
    Node * newNode = createNode(data);
    newNode->next = my_list->head;
    my_list->head = newNode;
    if (my_list->tail == NULL)
        my_list->tail = newNode;
}

void insertTail(List * my_list, int data) {
    Node * newNode = createNode(data);
    if (my_list->tail != NULL)
        my_list->tail->next = newNode;
    else

}

void deleteHead(List * my_list) {
    if (my_list == NULL) return;

    // Empty list check
    if (my_list->head == NULL) return 0;
}

int main() {
    List my_list;

    my_list.head = my_list
    return 0;
}