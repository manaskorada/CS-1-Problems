/* Manas Korada
COP 3502
0002
Where to Sit Program 1
10/6/2023
*/

// Included Libraries //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defined Constants //
#define MAX_PEOPLE 10
#define MAX_NAME 21

// Structures //
struct Attendee {
    char name[MAX_NAME]; // The name of the current attendee
    int popcorn; // An integer representing if the current attendee has popcorn. If it is 0 they don't have popcorn. If it is 1 they have popcorn
};

struct Pair {
    char name1[MAX_NAME]; // Name of the first attendee in the pair
    char name2[MAX_NAME]; // Name of the second attendee in the pair
};

// Type Definitions //
typedef struct Attendee Attendee;
typedef struct Pair Pair;

// Functions //

// Pre-Conditions: Takes in an array of attendees, an integer representing the number of people attending, an array of pairs of people that dislike each other, 
//                 and integer representing the number of pairs, and an array of integers representing the current permutation. 
// Post-Conditions: Returns 0 is the current permutation is not a valid permutation and 1 if the current permutation is a valid permutation based on the conditions that have already been set
int permutationValid(Attendee attendees[], int num_people, Pair pairs[], int num_pairs, int permutation[]) {
    // Checks if there are no pairs of people who dislike each other that are right next to each other in the current permutation
    for (int i = 0; i < num_people - 1; i++) {
        for (int j = 0; j < num_pairs; j++) {
            if ((strcmp(attendees[permutation[i]].name, pairs[j].name1) == 0 && strcmp(attendees[permutation[i + 1]].name, pairs[j].name2) == 0) ||
            (strcmp(attendees[permutation[i]].name, pairs[j].name2) == 0 && strcmp(attendees[permutation[i + 1]].name, pairs[j].name1) == 0)) {
                return 0; // If there are a pair of people who dislike each other that are right next to each other in the permutation it returns 0
            }
        }
    }

    // Checks if popcorn requirements are met. Each person must have popcorn or be next to someone who has popcorn (either before or after)
    for (int i = 0; i < num_people; i++) {
        if (attendees[permutation[i]].popcorn == 0) { // Checks if the current person in the permutation doesn't have popcorn
            if (i == 0 && attendees[permutation[i + 1]].popcorn == 0) { // If this person is the first in the permutation it checks the person right after
                return 0;
            } 
            if (i == num_people - 1 && attendees[permutation[i - 1]].popcorn == 0) { // If this person is the last in the permutation it checks the person right before
                return 0;
            } 
            if (attendees[permutation[i - 1]].popcorn == 0 && attendees[permutation[i + 1]].popcorn == 0) { // If this person is between the first and last, it checks the people before and after them
                return 0;
            }
        }
    }

    return 1;
}

// Pre-Conditions: Takes in an array of attendees, an integer representing the number of people attending, an array of pairs of people that dislike each other, 
//                 and integer representing the number of pairs, and an array of integers representing the current permutation, an array of integers which represent the names
//                 that have been used in the current permutation, the current position in the permutation, and an integer representing if this is the first pass of the function. 
// Post-Conditions: Returns an integer representing the number of valid permutation after the conditions have been given
int numPermutations(Attendee attendees[], int num_people, Pair pairs[], int num_pairs, int permutation[], int completed[], int current_position, int first_pass) {
    int count = 0; // Count is an integer that will hold the amount of valid permutations

    // Checks if current permutation is valid once the permutation array has been filled
    if (current_position == num_people) {
        if (permutationValid(attendees, num_people, pairs, num_pairs, permutation)) { // If the permutation is valid the function returns 1
            return 1;
        }
        if (first_pass != 0) { // If the function is not on its first pass then it will return 0 if the current permutation is not valid
            return 0;
        }
    }

    first_pass++; // The first_pass integer will only be 0 when this function is run for the first time

    // Goes through each permutation and check if it is valid based on the conditions using recursion
    for (int i = 0; i < num_people; i++) {
        // i is an integer that corresponds to the position of the attendee in the attendees array

        if (completed[i] == 0) { // First it checks if the current attendee has been used in the permutation
            completed[i] = 1; // If they haven't been used yet this value in the completed array will be set to 1 to show that they have been used
            permutation[current_position] = i; // Now the current position in the permutations array will be set to the appropriate attendee

            /* Using recursion, it will go to the next position in the current permutation until the permutation is filled.
               If the permutation is valid it will return 1 and the function will backtrack to the next permutation.
               These valid permutations will eventually be added up in the count integer
            */
            count += numPermutations(attendees, num_people, pairs, num_pairs, permutation, completed, current_position + 1, first_pass);

            completed[i] = 0; // Now the attendee will be removed from the completed array to show that they are no longer in use
        }
    }

    // Return the final amount of valid permutations
    return count;
}

// Main Function //
int main() {
    int num_people, num_pairs; // Integers represent the number of people and the number of pairs of people who dislike each other

    // Scans 2 integers representing the number of people and number of pairs of people who dislike each other respectively. Creates an array of attendees and pairs based on these integers
    scanf("%d %d", &num_people, &num_pairs);
    Attendee attendees[num_people];
    Pair pairs[num_pairs];

    // Scans in the names of the attendees and an integer representing if they have popcorn (1) or not (0). Stores this information in the attendees array
    for (int i = 0; i < num_people; i++) {
        scanf("%s %d", attendees[i].name, &attendees[i].popcorn);
    }
    // Scans in the 2 names for each pair of people that dislike each other. These are stored in the pairs array
    for (int i = 0; i < num_pairs; i++) {
        scanf("%s %s", pairs[i].name1, pairs[i].name2);
    }

    // An array of integers full of 0s that represents the attendees that have been used in the current permutation already.
    // The index in completed corresponds to the index of the attendees in the attendees array. 
    int completed[MAX_PEOPLE] = {0}; 

    // An array of integers representing the current permutation. The index in current permutation represents their position in the current permutation
    // The integer held in that position represents the position of the attendee in the attendees array
    int current_permutation[num_people]; 

    // Integer representing the current position in the current permutation
    int current_position = 0;
    // Integer that checks whether the function is on its first pass in 
    int first_pass = 0;
    // Calculates the count for the number of valid permutations
    int count = numPermutations(attendees, num_people, pairs, num_pairs, current_permutation, completed, current_position, first_pass);
    // Prints out this value
    printf("%d\n", count);
    
    // exits the program
    return 0;
}