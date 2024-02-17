/* Manas Korada
COP 3502
0002
Assignment 2
9/25/2023
*/

// Included Libraries //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct Customer Customer;
typedef struct Queue Queue;
typedef struct Booth Booth;

// Structures //
struct Customer {
    char * name; // name of customer
    int tickets; // number of tickets the customer purchases
    int line; // line or queue the customer is place in upon arrival
    int arrival; // time of arrival
};

struct Node {
    Node * next; // Pointer to the next node in the queue
    Customer * customer; // Pointer to a customer that is held within the node
};

struct Queue {
    Node * head, * tail; // Pointers to nodes representing the front and back of the queue
    int size; // Size or amount of people within the queue
    int booth; // The booth number that the queue is assigned to
};

struct Booth {
    int * queuesIncluded; // Array of integers representing the queue numbers that are included in this booth
    int numQueues; // Amount of queues within the within the booth
};

// Function Prototypes //
Customer * createCustomer(char * name, int tickets, int line, int arrival);
Node * createNode (Customer * customer);
Queue * initializeAllQueues();
void insertTail(Queue * queue, Customer * customer);
void removeHead(Queue * queue);
void enqueue(Queue * queue, Customer * customer);
void dequeue(Queue * queue);
int size(Queue * queue);
int empty(Queue * queue);
Customer * peek(Queue * queue);
int boothNotEmpty(Booth * booth, Queue * allQueues);

// Main function
int main() {
    int numCustomers, numBooths; // Integers representing the number of customers and the number of booths
    Queue * allQueues = initializeAllQueues(); // All 12 queues are created and put into an array of queues

    // Scan the number of customers and the number of booths
    scanf("%d %d", &numCustomers, &numBooths);

    // Initializes the data for the customers through user input, finds other data base on user input
    for (int i = 0; i < numCustomers; i++) {
        char name[52]; // String representing the name of the customer
        int tickets; // Number of tickets the customer purchases
        int arrival; // The time of arrival for the customer

        // Scans the name, ticket amount, and arrival time of each customer
        scanf("%s %d %d", name, &tickets, &arrival);

        // Finds the correct queue / line number to place the customer in
        int firstLetter = (int) name[0];
        firstLetter = firstLetter - 65;
        int queue = firstLetter % 13; // Queue number is found by finding the position of the first letter in the alphabet and using modulo 13

        if (queue == 0) { // If this comes out to 0, a different process is done to find the queue number
            int sizeOfQueue = 0;
            int count = 0;

            // Finds the first nonempty queue
            while (empty(&allQueues[count]) && count < 12) {
                count++;
            }

            if (count == 12) { // If all the queues are empty, the customer is assigned to queue 1
                queue = 1;
            } else { // If there are some nonempty queues, the customer is assigned to queue with the least number of customers that is nonempty
                sizeOfQueue = size(&allQueues[count]);
                queue = count + 1;

                // If the least number is the same for multiple queues, the queue number will not change and it will remain in the first queue with the smallest number
                for (int j = count; j < 12; j++) {
                    int tmp = allQueues[j].size;
                    if (tmp > 0 && tmp < sizeOfQueue) {
                        sizeOfQueue = tmp;
                        queue = j + 1;
                    }
                }
            }
        }

        // Create Customer and place into the appropriate queue
        enqueue(&allQueues[queue - 1], createCustomer(name, tickets, queue, arrival));
        allQueues[queue - 1].size = allQueues[queue - 1].size + 1; // The size of the queue that the customer was placed in is updated
    }

    // Finds the number of nonempty queues after all the customers have been assigned
    int nonEmptyQueues = 0;
    for (int i = 0; i < 12; i++) {
        if (!empty(&allQueues[i])) {
            nonEmptyQueues++;
        }
    }

    // Finds the number of queues per booth and the number of booths with an extra queue
    int queuesPerBooth = nonEmptyQueues / numBooths; // Represents the minimum number of queues that each booth will have
    int numBoothsExtra = nonEmptyQueues % numBooths; // Represents the number of booths that contain an extra queue

    // Creates an array of booths to hold the appropriate queue numbers that go to each booth
    Booth * booths = (Booth *) malloc(sizeof(Booth) * numBooths);

    int currentQueue = 0; // Reprsents the current queue as each queue is assigned to a booth

    // Stores the correct queues in the correct booths
    for (int i = 0; i < numBooths; i++) {
        // The booths with an extra queue assigned to them get their queue assignements first
        if (numBoothsExtra > 0) {
            // Creates an array of integers representing the queue numbers that go to the current booth
            booths[i].queuesIncluded = (int *) malloc(sizeof(int) * (queuesPerBooth + 1));
            booths[i].numQueues = queuesPerBooth + 1;

            // Finds the nonempty queues and starts assigning them to the booth from least to greatest
            for (int j = 0; j < queuesPerBooth + 1; j++) {
                while (empty(&allQueues[currentQueue]) && currentQueue < 12) {
                    currentQueue++;
                }

                // The queue number is added to the array of integers in the booth and the booth number is added to queue structure
                booths[i].queuesIncluded[j] = currentQueue;
                allQueues[currentQueue].booth = i + 1;
                currentQueue++; // The  current queue is updated
            }

            // The number of remaining booths that need an extra queue is updated
            numBoothsExtra--;
        } else { // Once there are no more booths that hold an extra queue, the remaining booths are initialized holding the normal amount of queues per booth
            booths[i].queuesIncluded = (int *) malloc(sizeof(int) * (queuesPerBooth));
            booths[i].numQueues = queuesPerBooth;

            for (int j = 0; j < queuesPerBooth; j++) {
                while (empty(&allQueues[currentQueue]) && currentQueue < 12) {
                    currentQueue++;
                }

                booths[i].queuesIncluded[j] = currentQueue;
                allQueues[currentQueue].booth = i + 1;
                currentQueue++;
            }
        }
    }

    // This is where the output statement is printed, the checkout time is calculated, and the customers get removed from the queues (dequeue)
    for (int i = 0; i < numBooths; i++) { // Goes through each booth
        int currentTime = 0; // Represents the current time in the simulation, used to calculate the check out times

        // Prints the booth number
        printf("Booth %d\n", (i + 1));
        
        int endingPoint = booths[i].numQueues; // Represents the ending queue in the booth that will be checked as the program searches for the next person to dequeue

        int QueueInBooth = boothNotEmpty(&booths[i], allQueues); // 1st Queue in booth that is not empty
        // Checks if the booth is not empty and goes through all the queues and customers at that booth until it is empty
        while (QueueInBooth != -5) {
            int endingQueue = booths[i].queuesIncluded[endingPoint - 1]; // Gives the current ending queue number in the booth

            // Updates the endpoint based on if the queues at the end of the booth are empty or not
            while (allQueues[endingQueue].size == 0) {
                endingPoint--;
                endingQueue = booths[i].queuesIncluded[endingPoint - 1];
            }

            // Sets the lowest arrival time to that of the customer at the head of the first nonempty queue
            int earliestQueue = QueueInBooth;
            int lowestStart = peek(&allQueues[QueueInBooth])->arrival;
            int startingPoint = 0;
            // Finds the starting queue number in the booth that corresponds to the first nonempty queue in the booth
            while (booths[i].queuesIncluded[startingPoint] != earliestQueue) {
                startingPoint++;
            }

            // Finds the queue with the earliest arrival time between the heads of queues within the booth and sets the earliest queue and lowest start time to the new values
            for (int j = startingPoint; j < endingPoint; j++) {
                // Finds the current queue number
                int currentQueue = booths[i].queuesIncluded[j];

                // Checks to see if the current queue is empty
                if(!empty(&allQueues[currentQueue])) {
                    Customer * newLowPoint = peek(&allQueues[currentQueue]); // Gets the pointer to the head of the current queue

                    // Checks to see if the head has a lower arrival time the current lowest
                    if (newLowPoint != NULL) {
                        int newLow = newLowPoint->arrival;
                        // If it has an earlier arrival time then it updates the new lowest arrival time and the queue with the highest priority
                        if (newLow < lowestStart) {
                            lowestStart = newLow;
                            earliestQueue = currentQueue;
                        }
                    }
                }
            }

            Customer * currentCustomer = peek(&allQueues[earliestQueue]); // Pointer to the customer with the highest priority in all the queues of the booth

            // Calculate the check out time of the current customer
            if (lowestStart > currentTime) { // If the customers arrival time is later than the current time it does not need to be considered to calculate their check out time
                currentTime = lowestStart + 30 + (5 * currentCustomer->tickets);
            } else { // If the arrival time is lower than the current time, the check out time is the current time + processing time
                currentTime = currentTime + 30 + (5 * currentCustomer->tickets);
            }
            // Current time will be updated to the check out time of the current customer

            // All information on customer has been calculated (name, line number, check out time)
            // Print output of their information on to the output
            printf("%s from line %d checks out at time %d.\n", currentCustomer->name, currentCustomer->line, currentTime);

            // The customer is removed from the queue and the size of the current queue is updated for future reference
            dequeue(&allQueues[earliestQueue]);
            allQueues[earliestQueue].size = allQueues[earliestQueue].size - 1;

            // The new first nonempty queue in the booth is calculated
            QueueInBooth = boothNotEmpty(&booths[i], allQueues);
        }
        
        // Current booth has been processed
        // Prints space for next Booth
        printf("\n");
    }
    
    // All the nodes, customers, and names have been freed with the dequeue
    // Queues array of 12 queues is freed
    free(allQueues);

    // Booths are freed along with their integer arrays
    for (int i = 0; i < numBooths; i++) {
        free(booths[i].queuesIncluded);
    }
    free(booths);

    // Exits the program
    return 0;
}

// Functions //
// Pre-Conditions: Takes in a pointer for a string representing the name of the customer, integer for number of tickets, integer for line number, integer for arrival time
// Post-Conditions: Returns the Customer structure created from this data
Customer * createCustomer(char * name, int tickets, int line, int arrival) {
    Customer * customer = (Customer *) malloc(sizeof(Customer));
    customer->name = strdup(name);
    customer->tickets = tickets;
    customer->line = line;
    customer->arrival = arrival;

    return customer;
}

// Pre-Conditions: Takes in a pointer to a Customer structure
// Post-Conditions: Returns a node holding the Customer structure given
Node * createNode (Customer * customer) {
    Node * res = (Node *) malloc(sizeof(Node));
    res->customer = customer;
    res->next = NULL;

    return res;
}


// Pre-Conditions: No preconditions
// Post-Conditions: Creates an array of 12 Queues to represent the 12 queues in the theater
Queue * initializeAllQueues() {
    Queue * allQueues = (Queue *) malloc(sizeof(Queue) * 12);
    for (int i = 0; i < 12; i++) {
        allQueues[i].head = allQueues[i].tail = NULL;
        allQueues[i].size = allQueues[i].booth = 0;
    }

    return allQueues;
}

// Pre-Conditions: Takes in a pointer to a Queue structure and a pointer to a Customer structure
// Post-Conditions: Creates a node holding the Customer structure and adds it to the end or tail of the Queue structure
void insertTail(Queue * queue, Customer * customer) {
    if (!queue) return; 
    Node * node = createNode(customer); 
    if (queue->tail) {
        queue->tail->next = node; 
        queue->tail = node; 
    } else {
        queue->tail = queue->head = node; 
    }
}

// Pre-Conditions: Takes in a pointer to a Queue structure
// Post-Conditions: Removes the node at the front or head of the Queue structure. Frees all the data within the node
void removeHead(Queue * queue) {
    if (!queue || !queue->head) return; 
    if (queue->head == queue->tail)  { 
        free(queue->head->customer->name);
        free(queue->head->customer);
        free(queue->head); 
        queue->head = queue->tail = NULL; 
        return;
    }
    Node * newHead = queue->head->next; 
    free(queue->head->customer->name);
    free(queue->head->customer);
    free(queue->head); 
    queue->head = newHead; 
}

// Pre-Conditions: Takes in a pointer to a Queue structure and a pointer to a Customer structure
// Post-Conditions: Creates a node holding the Customer structure and adds it to the end or tail of the Queue structure if the queue has been initialized
void enqueue(Queue * queue, Customer * customer) {
    if (queue) {
        insertTail(queue, customer);
    }
}

// Pre-Conditions: Takes in a pointer to a Queue structure
// Post-Conditions: Removes the node at the front or head of the Queue structure. Frees all the data within the node. Only does this if the queue has been initialized
void dequeue(Queue * queue) {
    if (queue) {
        removeHead(queue);
    }
}

// Pre-Conditions: Takes in a pointer to a Queue structure
// Post-Conditions: Returns the size or amount of nodes within the queue
int size(Queue * queue) {
    return queue->size;
}

// Pre-Conditions: Takes in a pointer to a Queue structure
// Post-Conditions: Returns 1 if the queue is empty and 0 if it is not empty
int empty(Queue * queue) {
    if (queue->size == 0) {
        return 1;
    }
    return 0;
}

// Pre-Conditions: Takes in a pointer to a Queue structure
// Post-Conditions: Returns customer at the head or front of the queue
Customer * peek(Queue * queue) {
    return queue->head->customer;
}

// Pre-Conditions: Takes in a pointer to a Booth structure and a pointer to a Queue structure
// Post-Conditions: Returns an integer representing first nonempty queue number within the booth, returns -5 if all the queues in the booth are empty
int boothNotEmpty(Booth * booth, Queue * allQueues) {
    int current;

    for (int i = 0; i < booth->numQueues; i++) {
        current = booth->queuesIncluded[i];

        if (empty(&allQueues[current]) == 0) {
            return current;
        }
    }
    return -5;
}