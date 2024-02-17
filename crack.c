#include <stdio.h>

void crack(int length, int loops_left, char * pass) {
    //BASE CASE: there are no more loops left
    if (loops_left == 0) {
        // Try pass
        printf("pass: %s\n", pass);

        // Exit
        return;
    }

    // RECURSIVE CASE: Try all possibilities for the letter
    for (char c = 'a'; c <= 'z'; c++) {
        // 1-indexed loops_left to 0-indexed array
        pass[loops_left - 1] = c;

        // Recursively brute force
        crack(length, loops_left - 1, pass);
    }

}

int main() {
    // Creating a password string
    char pass[5];
    pass[4] = 0;

    // Recursively crack the password
    crack(4, 4, pass);
}