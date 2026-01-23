#include <stdio.h>
#include <string.h>
struct Student {
    int roll;
    char grade;
    char name[50];
    int marks[3];
};
int main() {
    struct Student s1;

    // Assign values
    s1.roll = 1;
    s1.grade = 'A';

    // String assignment (character by character or using strcpy)
    strcpy(s1.name, "Krishna");

    // Array assignment
    s1.marks[0] = 85;
    s1.marks[1] = 90;
    s1.marks[2] = 88;

    // Print values
    printf("Roll No   : %d\n", s1.roll);
    printf("Grade     : %c\n", s1.grade);
    printf("Name      : %s\n", s1.name);

    printf("Marks     : ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", s1.marks[i]);
    }
    printf("\n");

    return 0;
}
