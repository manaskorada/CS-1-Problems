#include <stdio.h>
#include <string.h>

#define MAX_PEOPLE 10
#define MAX_NAME_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH];
    int popcorn;
} Person;

typedef struct {
    char name1[MAX_NAME_LENGTH];
    char name2[MAX_NAME_LENGTH];
} Constraint;

int count = 0;

int isValidPermutation(Person attendees[], int n, Constraint constraints[], int p, int permutation[]) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n - 1; j++) {
            if ((strcmp(attendees[permutation[j]].name, constraints[i].name1) == 0 &&
                 strcmp(attendees[permutation[j + 1]].name, constraints[i].name2) == 0) ||
                (strcmp(attendees[permutation[j]].name, constraints[i].name2) == 0 &&
                 strcmp(attendees[permutation[j + 1]].name, constraints[i].name1) == 0))
                return 0;  // Invalid permutation
        }
    }

    for (int i = 0; i < n; i++) {
        if (attendees[permutation[i]].popcorn == 1)
            continue;

        if ((i > 0 && attendees[permutation[i - 1]].popcorn == 1) ||
            (i < n - 1 && attendees[permutation[i + 1]].popcorn == 1))
            continue;
        else
            return 0;
    }

    return 1;
}

void generatePermutations(Person attendees[], int n, Constraint constraints[], int p, int permutation[], int used[], int pos) {
    if (pos == n) {
        if (isValidPermutation(attendees, n, constraints, p, permutation))
            count++;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            permutation[pos] = i;
            generatePermutations(attendees, n, constraints, p, permutation, used, pos + 1);
            used[i] = 0;
        }
    }
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);

    Person attendees[MAX_PEOPLE];
    for (int i = 0; i < n; i++)
        scanf("%s %d", attendees[i].name, &attendees[i].popcorn);

    Constraint constraints[MAX_PEOPLE];
    for (int i = 0; i < p; i++)
        scanf("%s %s", constraints[i].name1, constraints[i].name2);

    int permutation[MAX_PEOPLE];
    int used[MAX_PEOPLE] = {0};
    generatePermutations(attendees, n, constraints, p, permutation, used, 0);

    printf("%d\n", count);

    return 0;
}