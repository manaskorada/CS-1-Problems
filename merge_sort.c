#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void merge_sort(int * arr, int n) {
    if (n <= 1) return;
    int n2 = n / 2;

    merge_sort(arr, n2);
    merge_sort(arr + n2, n - n2);

    int * tmp = (int *) malloc(sizeof(int) * n);
    int fptr = 0;
    int bptr = n2;

    for (int i = 0; i < n; i++) {
        if (fptr == n2) {
            // front is empty
            tmp[i] = arr[bptr];
            bptr++;
        } else if (bptr == n) {
            // back is empty
            tmp[i] = arr[fptr];
            fptr++;
        } else if (arr[fptr] < arr[bptr]) {
            // front was smaller than the back
            tmp[i] = arr[fptr];
            bptr++;
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i] = tmp[i];
    }

    // Remove the temp arrau
    free(tmp);
}

#define DEFAULT_N 10

void gen_array(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
}

int main(int argc, char ** argv) {
    int n = DEFAULT_N;

    int 
}