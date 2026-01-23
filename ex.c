#include <stdio.h>
#include <string.h>

#define MAX 100

struct Employee {
    int id;
    char name[50];
    char dob[15];
    char doj[15];
    char designation[30];
    float salary;
};

struct Employee emp[MAX];
int count = 0;

/* Function declarations */
void addEmployee();
void displayEmployee();
void modifyEmployee();
void deleteEmployee();

int main() {
    int choice;

    do {
        printf("\n===== EMPLOYEE DATABASE MENU =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Modify Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            displayEmployee();
            break;
        case 3:
            modifyEmployee();
            break;
        case 4:
            deleteEmployee();
            break;
        case 5:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
void addEmployee() {
    if (count >= MAX) {
        printf("Employee database full!\n");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp[count].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", emp[count].name);

    printf("Enter Date of Birth (DD/MM/YYYY): ");
    scanf("%s", emp[count].dob);

    printf("Enter Date of Joining (DD/MM/YYYY): ");
    scanf("%s", emp[count].doj);

    printf("Enter Designation: ");
    scanf(" %[^\n]", emp[count].designation);

    printf("Enter Salary: ");
    scanf("%f", &emp[count].salary);

    count++;
    printf("Employee added successfully!\n");
}
void displayEmployee() {
    if (count == 0) {
        printf("No employee records found.\n");
        return;
    }

    printf("\n--- Employee List ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nEmployee %d\n", i + 1);
        printf("ID: %d\n", emp[i].id);
        printf("Name: %s\n", emp[i].name);
        printf("DOB: %s\n", emp[i].dob);
        printf("DOJ: %s\n", emp[i].doj);
        printf("Designation: %s\n", emp[i].designation);
        printf("Salary: %.2f\n", emp[i].salary);
    }
}
void modifyEmployee() {
    int id, found = 0;

    printf("Enter Employee ID to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", emp[i].name);

            printf("Enter new DOB: ");
            scanf("%s", emp[i].dob);

            printf("Enter new DOJ: ");
            scanf("%s", emp[i].doj);

            printf("Enter new Designation: ");
            scanf(" %[^\n]", emp[i].designation);

            printf("Enter new Salary: ");
            scanf("%f", &emp[i].salary);

            printf("Employee updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");
}
void deleteEmployee() {
    int id, found = 0;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                emp[j] = emp[j + 1];
            }
            count--;
            printf("Employee deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");
}
