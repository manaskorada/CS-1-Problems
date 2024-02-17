/* Manas Korada
COP 3502
0002
Financial Aid Assignment
8/24/2023
*/

// Included Libraries
#include <stdio.h>
#include <string.h>

// Main function
int main(void) {
    /*
    original holds the string for the original sign, 
    desired holds the string for the desired sign, 
    frequencyO is a frequency array that holds the number of each capital letter character within the original string,
    frequencyD is a frequency array that holds the number of each capital letter character within the desired string,
    value represents the ASCII value of each character in the string as it goes through the for loop,
    diff represents the difference in the number of characters with the same ASCII values in between the two frequency arrays,
    originalLength represents the length for the original string,
    desiredLength represents the length for the desired string,
    count represents the number of letters that need to be purchased and is the output
    */
    char original[100002];
    char desired[100002];
    int frequencyO[26];
    int frequencyD[26];
    int value, diff, originalLength, desiredLength;
    int count = 0;

    // Collects the original and desired strings through user input
    fgets(original, 100002, stdin);
    fgets(desired, 100002, stdin);

    // Calculates the length of the original and desired string
    originalLength = strlen(original) - 1;
    desiredLength = strlen(desired) - 1;

    // fills out the frequency array for the original string by going through each character 
    for (int i = 0; i < originalLength; i++) {
        value = original[i]; 

        for (int j = 0; j < 26; j++) {
            if (value == j + 65) {
                frequencyO[j]++;
            }
        }
    }

    // fills out the frequency array for the desired string by going through each character 
    for (int i = 0; i < desiredLength; i++) {
        value = desired[i]; 

        for (int j = 0; j < 26; j++) {
            if (value == j + 65) {
                frequencyD[j]++;
            }
        }
    }

    // Calculates the count for the number of letters that need to be purchased by finding the difference in the frequency of each character and adding more to the count if more are needed
    for (int i = 0; i < 26; i++) {
        diff = frequencyD[i] - frequencyO[i];

        if (diff > 0) {
            count += diff;
        }
    }

    // Prints out the final output for the number of letters that need to be purchased
    printf("%d", count);

    return 0;
}