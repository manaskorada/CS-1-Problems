#include <stdio.h>
#include <stdlib.h>

int main() {
    int N = 10000000;

    int ans = 0;
    while (N) {
        N = rand() % N; // make N in range of 0 to N-1
        for (int i = 0; i < N; i++) {
            ans += rand(); // loop number of times equal to new N
        }
    }

    // Average Case
    // T(N) = (1/N)(T(0)+T(1)+T(2)+...+T(N-1)+N-1)
    // T(0) = 0

    return 0;
}