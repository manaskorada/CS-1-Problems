#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Group {
    double angle;
    int size;
};

int compare(const void *a, const void *b) {
    return (*(struct Group *)a).angle - (*(struct Group *)b).angle;
}

int main() {
    int N, A;
    scanf("%d %d", &N, &A);

    struct Group groups[N];

    for (int i = 0; i < N; i++) {
        double x, y;
        int s;
        scanf("%lf %lf %d", &x, &y, &s);
        groups[i].angle = atan2(y, x) * (180.0 / 3.14159265358979323846); // Convert to degrees
        groups[i].size = s;
    }

    qsort(groups, N, sizeof(struct Group), compare);

    int minPeople = N; // Initialize with the maximum possible value

    for (int i = 0; i < N; i++) {
        int currentPeople = 0;

        for (int j = i; groups[j].angle - groups[i].angle <= A; j = (j + 1) % N) {
            currentPeople += groups[j].size;
        }

        if (currentPeople < minPeople) {
            minPeople = currentPeople;
        }
    }

    double maxAngleWithoutPeople = groups[0].angle - groups[N - 1].angle + 360.0;

    printf("%d\n%.4lf\n", minPeople, maxAngleWithoutPeople);

    return 0;
}