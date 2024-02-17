#include <stdio.h>
#include <stdlib.h>

struct author_t
{
    char name[20];
    int birthYear;
    int publishings;
};

struct book_t
{
    char name[20];
    int year;
    int numAuthors;
    struct author_t * authors;
};

int main() {
    int n;
    scanf("%d", &n);



    return 0;
}


/*
Create an entrance point for the rows. For each row, there is a dynamic array attached. In each cell of the array, there is a 
representation of the reservation

Have to figure out whether you can successfully reserve it or not



*/