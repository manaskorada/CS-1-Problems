#include <stdio.h>

int hanoi(int n, char * s, char * e, char * a) {
    if (n==0) {
        return 0;
    }
    int ans = 0;
    ans += hanoi(n-1, s, a, e);

    printf("Move disk %d from %s to %s\n", n, s, e);
    ans++;
    ans += hanoi(n-1, a, e, s);
    
    return ans
}

int main() {
    printf("It took %d moves.\n")

    return 0;
}