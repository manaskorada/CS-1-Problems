/* Manas Korada
COP 3502
0002
Projector Problem
10/28/2023
*/

// Included Libraries //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Defined Constants //

// Structures //
struct Group {
    double angle;
    int size;
};

typedef struct Group Group;

// Functions //
// Pre-Conditions: Takes in a pointer an array of groups and an integer representing the number of groups
// Post-Conditions: Sorts the array of groups by angle from lowest angle to greatest angle
void merge_sort(Group * allGroups, int num_groups) {
    // Base case
    if (num_groups <= 1) {
        return;
    }

    // Compute number of half the array
    int half = num_groups / 2;

    merge_sort(allGroups, half);
    merge_sort(allGroups + half, num_groups - half);

    Group * tmp = (Group *) malloc(sizeof(Group) * num_groups);
    int fptr = 0; // front of the first half
    int bptr = half; // front of the back half

    for (int i = 0; i < num_groups; i++) {
        if (fptr == half) {
            // front is empty
            tmp[i] = allGroups[bptr];
            bptr++;
        } else if (bptr == num_groups) {
            // back is empty
            tmp[i] = allGroups[fptr];
            fptr++;
        } else if (allGroups[fptr].angle < allGroups[bptr].angle) {
            // front was smaller than the back
            tmp[i] = allGroups[fptr];
            fptr++;
        } else {
            // back was good enough
            tmp[i] = allGroups[bptr];
            bptr++;
        }
    }

    // Move temp values into original array
    for (int i = 0; i < num_groups; i++) {
        allGroups[i] = tmp[i];
    }

    free(tmp); // Remove the temp array
}

// Main function //
int main() {
    // num_groups is an integer representing the number of groups, initial_angle is the angle the user gives for the projection
    int num_groups, initial_angle; 

    // Scans in the information for the number of groups and the projection angle
    scanf("%d %d", &num_groups, &initial_angle);

    // Creates an array of groups with the size num_groups
    Group * allGroups = (Group *) malloc(sizeof(Group) * num_groups);
    for (int i = 0; i < num_groups; i++) {
        // x and y represent the x and y positions of the current group 
        double x, y;
        int s; // s is the number of people in the group

        // Takes in the data for each group and calculates the angle of the group. Holds this information in the allGroups array
        scanf("%lf %lf %d", &x, &y, &s);
        allGroups[i].size = s;
        allGroups[i].angle = atan2(y, x) * (180.0 / 3.14159265358979323846);
    }

    // Sort the groups of people by angle from lowest angle to highest
    merge_sort(allGroups, num_groups);

    // array holding the the angle between adjacent groups in the allGroups array
    double angles_seperating[num_groups];

    // Finding max angle without people
    double max_angle;
    if (num_groups == 1) { // If there is only 1 group then the max angle is almost 360 degrees
        max_angle = 360;
    } else {
        // finds the angle between the first group and the second group and holds this in the first element in the angle_seperating array
        max_angle = allGroups[1].angle - allGroups[0].angle;
        angles_seperating[0] = max_angle;

        // populates the angles_seperating array with the angles between adjacent elements and finds the greatest angle
        for (int i = 1; i < num_groups - 1; i++) {
            double temp_angle = allGroups[i + 1].angle - allGroups[i].angle;
            angles_seperating[i] = temp_angle;

            if (temp_angle > max_angle) { 
                max_angle = temp_angle;
            }
        }

        // The final angle in the angles_seperating array is the angle between the first group and the last group in the allGroups array
        double temp_angle = 360 - (allGroups[num_groups - 1].angle - allGroups[0].angle);
        angles_seperating[num_groups - 1] = temp_angle;
        
        // If this last angle is greater than the current max angle, the max angle will be set to this last angle
        if (temp_angle > max_angle) {
            max_angle = temp_angle;
        }
    }

    // finding minimum number of people with given projection, 
    int minimum_people;

    if (max_angle >= initial_angle || num_groups == 1) {
        // If we know the maximum angle without people is greater than or equal to the initial angle 
        // we can just say that the minimum people is 0
        minimum_people = 0;
    } else {
        // minimum people is initially set to the maximum number of people that are possible with all the groups
        minimum_people = 500000000;
        // startL and endL represent the start and end of the current angle if we are increasing the angle in the clockwise direction
        // startR and endR represent the start and end of the current angle if we are increasing the angle in the counterclockwise direction
        int endL, startL, endR, startR;

        // current_peopleL represent the number of people in the current angle if we are increasing the angle in the clockwise direction
        // current_peopleR represent the number of people in the current angle if we are increasing the angle in the counterclockwise direction
        int current_peopleR;
        int current_peopleL;

        // temp_angleL represent angle between the start and end of the current angle if we are increasing the angle in the clockwise direction
        // temp_angleR represent angle between the start and end of the current angle if we are increasing the angle in the counterclockwise direction
        double temp_angleR;
        double temp_angleL;

        // Now we go through each group as the starting point and increase it from the clockwise or 
        // counterclockwise direction until it is greater than or equal to the angle that was given
        for (int i = 0; i < num_groups; i++) { // i is the starting point
            if (i == 0) { 
                // When we are at the first element in the allGroups array the start of the angle is the last element in the group and the end is the second element
                temp_angleL = angles_seperating[0] + angles_seperating[num_groups - 1];
                temp_angleR = temp_angleL;
                startL = num_groups - 1;
                startR = num_groups - 1;
                endL = 1;
                endR = 1;
            } else {
                // In all other cases the start of the angle is at the element right before the current elementa and the end is at the element right after
                temp_angleL = angles_seperating[i] + angles_seperating[i - 1];
                temp_angleR = temp_angleL;
                startL = i - 1;
                startR = i - 1;
                endL = i + 1;
                endR = i + 1;

                // If the end ends up being greater than the last index, the end index if updated to 0
                if (endL == num_groups) {
                    endL = 0;
                    endR = 0;
                }
            }

            // The current amount of people in the current angle is set to the size of the current group
            current_peopleL = allGroups[i].size;
            current_peopleR = allGroups[i].size;


            // This loop increases the angle from the clockwise direction until is is greater than or equal to the angle given
            // It finds the number of people held in this angle afterwards 
            while (startL != endL && temp_angleL < initial_angle) {
                // first the starting index is moved back
                startL--;
                if (startL < 0) { // if the index is less than 0, it loops back to the last element in the groups
                    startL = num_groups - 1;
                }

                // Updates the temp angle until it is greater than the angle given
                temp_angleL = temp_angleL + angles_seperating[startL]; 

                // Finds the index within the allGroups array to add to the total amount of people in the angle
                int added_people_index = startL + 1;
                if (added_people_index >= num_groups) {
                    added_people_index = 0;
                }

                // Updates total amount of people in the angle
                current_peopleL = current_peopleL + allGroups[added_people_index].size;
            } 

            // This loop increases the angle from the counterclockwise direction until is is greater than or equal to the angle given
            while (startR != endR && temp_angleR < initial_angle) {
                // first the ending index is moved forward
                endR++;
                if (endR >= num_groups) { // if the index is greater than the last index, it loops back to the first element in the groups
                    endR = 0;
                }

                // Finds the index of the angle that needs to be added and the group of people that needs to be added
                int end_angle_index = endR - 1;
                if (end_angle_index < 0) {
                    end_angle_index = num_groups - 1;
                }
                // Updates the temp angle until it is greater than or equal to the initial angle
                temp_angleR = temp_angleR + angles_seperating[end_angle_index]; 
                // Updates the total amount of people based on this angle
                current_peopleR = current_peopleR + allGroups[end_angle_index].size;
            } 

            // Now that we have the amount of people if you increased the angle from the clockwise and counterclockwise direction,
            // you find which one has less people and set current_peopleL to this lower value
            if (current_peopleR < current_peopleL) {
                current_peopleL = current_peopleR;
            }

            // If this value is less than the current minimum, the current minimum will be set to this new minimum
            if (current_peopleL < minimum_people) {
                minimum_people = current_peopleL;
            }
        }
        // By the end of this for loop we should have the smallest amount of people while maintaining the projection angle

        
    }

    // Prints out output
    printf("%d\n", minimum_people);
    printf("%.4lf\n", max_angle);
    
    // Frees the allGroups array
    free(allGroups);

    // exits program
    return 0;
}