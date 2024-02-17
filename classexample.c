// Include the standard library header (contains dynamic memory functions)
#include <stdlib.h>

// A custom Student data structure
struct Student
{
    int grade; // The grade of the student
    char * name; // use dynamic blocks to save memory when possible
};

// A custom class data structure
struct Class
{
    struct Student * roster; // Array of student in the class
    int enrollment; // The number of students in the class
    int capacity; // The maximum allowed number of students in the class
};

// typedefs can be used to alias types
typedef struct Class Class;

// Instantiate a Class dynamically
// Initialize the Class
// Return it.
Class * createClass(int initial_cap)
{
    // Create the block of memory holding the class
    Class * res = (Class *) malloc(sizeof(Class));
    // Fill in the initial capacity
    res->capacity = initial_cap;
    // Set there are 0 students in the class
    (*res).enrollment = 0;
    
    // Create the roster of students based on the capacity
    res->roster = (struct Student *)
                    malloc(sizeof(struct Student) *
                    initial_cap);

    // Return the resulting class structure
    return res;
}

// The main function
int main()
{
    // My class pointer
    struct Class * my_class;
    
    // Allocate memory for the class
    my_class = createClass(250);

    // free the class when I'm finished
    free(my_class->roster); // free roster first to avoid use after free
    free(my_class); // Free the class last

    // exit the program
    return 0;
}
