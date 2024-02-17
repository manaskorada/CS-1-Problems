#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct LL LL;

struct Node {
    int data;
    Node * next;

};

struct LL {
    Node * head;
    Node * tail;
    int num_nodes;

};

void headInsertion(LL * list, int data) {
    Node * newNode = (Node *) malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = list->head;

    list->head = newNode;
    list->tail = newNode;

    list->num_nodes++;
}

void tailInsertion(LL * list, int data) {
    Node * newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node * oldTail = list->head;
    if(oldTail == NULL) {
        list->head = newNode;
        list->num_nodes++;
        return;
    }
    // Loop until the oldTail is the tail
    while (oldTail->next != NULL) {
        oldTail = oldTail->next;

    }

    // old tail is old tail
    oldTail->next = newNode;
    list->num_nodes++;
}

void printList(LL list) {
    Node * cur = list.head;

    printf("")

    // Make sure to stop when hitting 
    // NULL
    while (cur != NULL) {
        // Print the value out

        // Moving to the next location
        cur = cur->next;
    }

    printf("NULL\n");
}

void cleanList(LL list) {
    Node * curNode = list.head;
    for (int i = 0; i < list.num_nodes; i++) {

        Node * nextNode = curNode->next;
        free(curNode);
        curNode = nextNode;
    }
}

int isEmpty(LL * my_list) {
    return (my_list->head == NULL);
}

void deleteHead(LL * my_list) {
    if (my_list == NULL) return;

    // Empty list check
    if (my_list->head == NULL) return;

    // Store the old head address
    Node * oldHead = my_list->head;

    // Point to the new head
    my_list->head = my_list->head->next;

    // Free the old node
    free(oldHead);
}
 
void cleanList(LL * my_list) {
    while(!isEmpty(my_list)) {
        deleteHead(my_list);
    }
}

void printList(LL * my_list) {
    Node * cur = my_list->head;

    while(cur != NULL) {
        printf("%d -> ", cur->data);
        
    }
}

int main() {
    LL list;


    // initialize the list
    list.head = NULL;
    list.num_nodes = 0;
    

    /*
    headInsertion(&list, 3);
    headInsertion(&list, 1);
    headInsertion(&list, 4);
    headInsertion(&list, 1);
    headInsertion(&list, 5);
    */



    // Print the list
    printList(list);

    // Remove List(clean up any memory)
    cleanList(list);
    return 0;
}