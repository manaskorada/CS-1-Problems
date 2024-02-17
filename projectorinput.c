#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Number of groups and initial angle
    int N = 50;
    int A = 70;

    // Create and open the input file for writing
    FILE *file = fopen("input.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the number of groups and initial angle to the file
    fprintf(file, "%d %d\n", N, A);

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate random group data and write it to the file
    for (int i = 0; i < N; i++) {
        int x = rand() % 2000001 - 1000000;
        int y = rand() % 2000001 - 1000000;
        int s = rand() % 1000 + 1;
        fprintf(file, "%d %d %d\n", x, y, s);
    }

    // Close the file
    fclose(file);

    return 0;
}
