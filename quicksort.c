#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void gen_array(int * arr, int n);

void swap (int * a, int * b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quick_sort_array(int * arr, int n) {
    if (n <= 1) {
        return; // Already sorted
    }
    int pivotValue = arr[0];
    int fPtr = 1;
    int bPtr = n - 1;

    for (int i = 0; i < n - 1; i++) {
        if (pivotValue < arr[fPtr]) {
            // TOO BIG
            // Move to back
            swap(arr + fPtr, arr + bPtr);

            // Update the bptr
            bPtr--;

        } else {
            // SMALL ENOUGH
            // LEAVE the value in the spot (do nothing)
            // Update front pointer
            fPtr++;
        }
    }

    // Move pivot into correct location
    swapt(arr + 0, arr + bptr);

    // Sort recursively
    quick_sort_array(arr, bptr);
    quick_sort_array(arr + bptr + 1, n - (bptr + 1));
}

void print_array(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i == n-1) printf("\n");
        else printf(" ");
    } 
}

void check_sorted_array(int * arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        assert(arr[i] <= arr[i + 1]);
    }
}

int main(int argc, char ** argv) {
    int n ;
}