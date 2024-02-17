/* Manas Korada
COP 3502
0002
Financial Aid Assignment
9/10/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_CAP 4

typedef struct student student;
typedef struct list list;

struct student {
    char * name;
    int grade;
};

struct list {
    student * array;
    int size;
    int cap;
};

list * createList() {
    list * result;
    result = (list *) malloc(sizeof(list));
    result->array = (student *) malloc(sizeof(student) * DEFAULT_CAP);// TODO
    result->size = 0;
    result->cap = DEFAULT_CAP;
    
    // Return the address of the list created dynamically
    return result;
}

void append(list * my_list, char * name, int grade) {
    if (my_list->size == my_list->cap) {
        // expand the list
        my_list->array = (student *) realloc(my_list->array,
                                            2*my_list->cap*sizeof(student));

        my_list->cap *= 2;
    }   

    // Put the value in the correct location (size)
    my_list->array[my_list->size].grade = grade;
    my_list->array[my_list->size].name = strdup(name);

    // Update the size of the list
    my_list->size++;
}

void printStudent(student * cur_student) {
    printf("%s %d\n", cur_student->name, cur_student->grade);
}

void printList(list * my_list) {
    for (int i = 0; i < my_list->size; i++) {
        printStudent(my_list->array + i);
    }
}

void deleteList(list * my_list) {
    for (int i = 0; i < my_list->size; i++) {
        free(my_list->array[i].name);
    }
    
    free(my_list->array);
    free(my_list);
}

int main() {
    list * my_list;
    my_list = createList();
    
    append(my_list, "Alice", 100);
    append(my_list, "Jeff", 99);
    append(my_list, "Travis", 65);
    append(my_list, "Doug", 90);
    append(my_list, "Rodric", 30);
    append(my_list, "James", 96);
    append(my_list, "Jane", 86);
    append(my_list, "Gym", 3);
    append(my_list, "Bobber", 45);
    append(my_list, "Carol", 70);

    printList(my_list);
    
    deleteList(my_list);
    return 0;
}