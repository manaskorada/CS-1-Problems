// This program demonstrates the selection sort

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEFAULT_N 10

void gen(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

void print(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i == n-1) printf("\n");
        else printf(" ");
    }
}

void sel_sort(int * arr, int n) {
    for (int i = 0; i < n -1; i++) {
        int * best = arr + i;
        for (int j = i + 1; j < n; j++) {
            if (*best > arr[j]) {
                best = arr + j;
            }
        }

        int tmp = * best;
        *best = arr[i];
        arr[i] = tmp;
    }

    
}

void verify_sorted(int * arr, int n) {
    for (int i = 0; i < )
}

int main(int * arr, int n) {
    int n = DEFAULT_N;
    
    gen(arr, n);
    print(arr, n);
    sel_sort(arr, n);
    print(arr, n);
    verify_sorted(arr, n);
}

