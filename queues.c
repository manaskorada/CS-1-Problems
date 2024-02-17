// Header files
#include <stdio.h>
#include <stdlib.h>

// Struct Aliases
typedef struct List List;
typedef struct Node Node;
typedef struct Queue Queue;

// Struct Definitions
struct List {
    Node * head, * tail;
};

struct Queue {
    List * lst;
};

struct Node {
    Node * nxt;
    int data;
};

Node * createNode(int data)
{   // allocate memory for a new node in your list and
    // fill the node with the data passed into our createNode function
    Node * res = (Node *) malloc(sizeof(Node));
    res->data = data;
    res->nxt = NULL;
    return res;
}

List * createList()
{   // allocate memory for a new list and set the head& tail to null
    List * res = (List *) malloc(sizeof(List));
    res->head = res->tail = NULL;
    return res;
}

Queue * createQueue()
{   // allocate memory for a new queue and return the new queue
    Queue * res = (Queue *) malloc(sizeof(Queue));
    res->lst = createList();
    return res;
}

void insertTail(List * l, int v)
{
    if (!l) return; // if the list doesnt exist, return
    Node * r = createNode(v); // create a node with passed in value
    if (l->tail)
    {
        l->tail->nxt = r; // add the new node to our old tail's next
        l->tail = r; // update the list's tail to point to the new tail
    } else
    {
        l->tail = l->head = r; // if list was empty, set the new node to the tail AND head
    }
}

void removeHead(List * l)
{
    if (!l || !l->head) return; // if there is no list or no list head, then stop! or segfault
    if (l->head == l->tail) // if the head and tail are the same node
    {
        free(l->head); // free the head, which effectively also removes the tail
        l->head = l->tail = NULL; // update the list to tell us we no longer have head or tail
        return;
    }
    Node * newHead = l->head->nxt; // set cur head's next to be the new head
    free(l->head); // now we can free our old head
    l->head = newHead; // have list's head point to our newHead
}

void dequeue(Queue * q)
{   // queues work by first in first out so we need to remove the node
    // that was entered first, which was the head
    if (q)
        removeHead(q->lst); // so if our queue exists, we call to remove the head
}

void enqueue(Queue * q, int v)
{   // because queues work first in first out, we need to add any
    // new node to the back of the line. kinda like a line at disney
    if (q)
        insertTail(q->lst, v); // so if a queue exists, insert the new value at the end of it
}

int front(Queue * q)
{
    return q->lst->head->data; // return the data inside the head of the list
}

void deleteList(List * l)
{
    while (l->head) removeHead(l); // while list has a head, we will call the removeHead function
    free(l); // we will free the list after all it's contents are removed, so we dont leak memory
}

void deleteQueue(Queue * q)
{
    deleteList(q->lst); // we will free the list associated with the queue
    free(q); // now free queue itself
}

// The main function
int main()
{
    // Create a queue dynamically
    Queue * q = createQueue();
    // Enqueue the values 1 through 4
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    // Repeatedly remove the first value from the queue and add that value to the end of the queue twice
    for (int i = 0; i < 10; i++)
    {
        int f = front(q);
        dequeue(q);
        enqueue(q, f);
        enqueue(q, f);
        // Print the value removed
        printf("%d\n", f);
    }
    // Clean up the memory
    deleteQueue(q);
    // Exit the program
    return 0;
}