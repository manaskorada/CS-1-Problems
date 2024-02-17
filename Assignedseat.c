/* Manas Korada
COP 3502
0002
Financial Aid Assignment
9/10/2023
*/

// Included Libraries //dBU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defined Constants //
#define DEFAULT_CAP 4

// Structures //
struct Reservation {
    int start, end; // Start and end of reservation
    char * name; // Name of person reserving this range
};

struct Row {
    struct Reservation * array; // array of reservations
    int max_reservations; // the spots in the array
    int num_reservations; // occupied spots in the array
};

struct Theater {
    struct Row * row; // The array of rows in the theater
};

typedef struct Theater Theater;
typedef struct Row Row;
typedef struct Reservation Reservation;

// Functions //

// Pre-Conditions: Takes in a pointer to a Row structure. In the main function this points to a Row in the row array in the Theater structure
// Post-Conditions: Allocates space initially in the row for 4 reservations. Sets the values of the max reservations and number of reservations in the Row. 
void InitializeRow(Row * row) {
    row->array = (Reservation *) malloc(sizeof(Reservation) * DEFAULT_CAP);
    row->max_reservations = DEFAULT_CAP;
    row->num_reservations = 0;
}

// Pre-Conditions: Takes in pointer to a row, 2 integers for the start and end of the seats purchased, and a pointer to a string representing the name of the person making the purchase
// Post-Conditions: Returns 0 if the purchase was a failure. Returns 1 if the purchase was a success. In this situation, the num_reservations is updated and the reservation
// is initialized with the proper values. This is also where dynamic allocation of the reservation array for each row is done. 
int makePurchase(Row * row, int start, int end, char * name) {
    int reservationNumber = row->num_reservations;

    // Goes through the reservation array in the array to check if the any of the previous reservations overlap with the purchase
    for (int i = 0; i < row->num_reservations; i++) {
        if (start <= row->array[i].end && end >= row->array[i].start) {
            return 0; // Returns 0 when the purchase was a failure
        }
    }

    // Initializes the purchase if there are no overlaps with previous reservations in the reservation array
    row->array[row->num_reservations].start = start;
    row->array[row->num_reservations].end = end;
    row->array[row->num_reservations].name = strdup(name);

    // Updates the num_reservations variable in the Row structure to match the new number of reservations
    row->num_reservations = row->num_reservations + 1;

    // Dynamic Allocation of Reservation Array of Rows. The reservation array updates whenever the number of reservations reaches the max reservations. 
    int max = row->max_reservations;
    if (max == row->num_reservations) {
        max = max * 2;
        row->array = (Reservation *) realloc(row->array, max * sizeof(Reservation));
    }
     
    return 1; // Returns 1 when the purchase was successful
}

// Pre-Conditions: Takes in a pointer to a row and an integer representing the seat in the row that the user want to look up
// Post-Conditions: Prints out the name of the person who owns the seat or the phrase: "No one" if nobody owns that seat
void lookUp(Row * row, int seat) {
    int count = row->num_reservations;
    int found = 1;
    int i = 0;
    
    // Checks through the reservation array and prints out the name of the person who has reserved the seat
    while (i < count && found == 1) {
        if (row->array[i].start <= seat && row->array[i].end >= seat) {
            printf("%s\n", row->array[i].name);
            found--;
        }
        i++;
    }
    
    // Prints out "No one" if nobody has purchased the the seat that is being looked up
    if (found == 1) {
        printf("No one\n");
    }
}

// Pre-Conditions: Takes in a pointer to a Theater structure
// Post-Conditions: Uses the free function where needed to prevent memory leaks
void clearTheater(Theater * theater) {
    for (int i = 0; i < 100000; i++) {
        int row_size = theater->row[i].num_reservations;

        for (int j = 0; j < row_size; j++) {
            free(theater->row[i].array[j].name);
        }

        free(theater->row[i].array);
    }

    free(theater->row);
    free(theater);
}

// Main function
int main() {
    int stop = 1;

    // Initializes the theater structure dynamically
    // Allocates space for the rows array in for 100000 rows
    Theater * my_theater = (Theater *) malloc(sizeof(Theater));
    my_theater->row = (Row *) malloc(sizeof(Row) * 100000);
    
    // Loops until the user enters "QUIT"
    while (stop == 1) {
        // Command is a string that is scanned in from user input so the program understands which process to go through (BUY, LOOKUP, QUIT)
        char command[10];
        scanf("%s", command);

        // If the user enters BUY along with the associated input values it will use the initializeRow function and the makePurchase function to print out the correct output store
        // the purchase information.
        if (strcmp(command, "BUY") == 0) {
            // When the user enters BUY, integers representing the row, start, and end of the purchase are scanned in. A string for the name the purchase is under is also taken in
            int start, end, row;
            char name[52];
            
            scanf(" %d %d %d %s", &row, &start, &end, name);

            // If the row hasn't been initialized yet, the appropriate row is initialized with the InitializeRow function
            if(my_theater->row[row - 1].max_reservations == 0) {
                InitializeRow(&my_theater->row[row - 1]);
            }

            // Goes through the makePurchase function to store the purchase and print out whether the purchase was a success or failure
            int result = makePurchase(&my_theater->row[row - 1], start, end, name);

            if (result == 1) {
                printf("SUCCESS\n");
            } else {
                printf("FAILURE\n");
            }

        } else if (strcmp(command, "LOOKUP") == 0) {
            // If the user enters LOOKUP along with the appropriate values, the values are fed to the lookUp function to print the correct output
            int lookup_row, lookup_seat;

            scanf(" %d %d", &lookup_row, &lookup_seat);

            lookUp(&my_theater->row[lookup_row - 1], lookup_seat);

        } else if (strcmp(command, "QUIT") == 0) {
            // the loop ends when the user enters QUIT
            stop--;
        } 
    }

    // Frees the theater along with the rows array and the array for the reservations in each row
    clearTheater(my_theater);

    // exits the program
    return 0;
}