#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    int N = DEFAULT_N;
    int fast = DEFAULT_SPEED;
    int ans = 0;

    if (argc > 1) {
        N = atoi(argv[1]);
    }
    if (argc > 2) {
        fast = atoi(argv[2]);
    }

    if (fast) {
        // Prime sieve
        int *is_prime = (int *) malloc(sizeof(int) * (N+1));


        for (int i = 0; i <= N; i++) {
            is_prime[i] = 1;
        }
        is_prime[1] = is_prime[0] = 0;

        // Loop through all values up to N
        for (int i = 0; i <= N; i++) {
            // Check if the number is prime
            if (is_prime[i]) {
                ans += i;
                // Mark out the multiples of a prime
                for
            }
        }
    }
}