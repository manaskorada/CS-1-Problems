#include <stdio.h>

int check(int * perm, int n) {
    for (int cur = 0; cur < n; cur++) {
        int other
    }
}

void printArray(int * arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void solve(int * perm, int length, int loop_left) {
    if (loop_left == 0) {
        if (check(perm, length)) {
            printArray(perm, length);
        }
        return;
    }

    for (int i = 0; i < loop_left; i++) {
        // fill in spot at loop_left - 1
        int tmp = perm[i];
        perm[i] = perm[loop_left - 1];
        perm[loop_left - 1] = tmp;

        // Recurse
        solve(perm, length, loop_left);

        // Undo the swap made to form the permutation
        tmp = perm[i];
        perm[i] - perm[loop_left-1];
    }
}

int main() {
    // Create initial puzzle state
    int perm[8];

    perm[0] = perm[1] = 1;
    solve(perm, 8, 8);
}