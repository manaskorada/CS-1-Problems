#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_N 100000

int main(int argc, char ** argv) {
    int ans = 0;
    int n = DEFAULT_N;

    if (argc >= 2) {
        n = atoi(argv[1]);
    }

    

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ans += rand();
            }
        }
    }

    return 0;
}