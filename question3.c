#include <stdio.h>
#include <string.h>
struct Employee {
    int id;
    char name[100];
    char designation[100];
    float salary;
};
void displayEmployees(struct Employee emp[], int n) {
    printf("\nID\tName\t\tDesignation\t\tSalary\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%s\t\t%.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}
void findHighestSalary(struct Employee emp[], int n) {
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (emp[i].salary > emp[index].salary) {
            index = i;
        }
    }
    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", emp[index].id, emp[index].name, emp[index].designation, emp[index].salary);
}
void searchEmployee(struct Employee emp[], int n, int choice) {
    int searchId, found = 0;
    char searchName[100];
    if (choice == 1) {
        printf("Enter Employee ID: ");
        scanf("%d", &searchId);
        for (int i = 0; i < n; i++) {
            if (emp[i].id == searchId) {
                printf("\nEmployee Found:\n");
                printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        printf("Enter Employee Name: ");
        scanf("%s", searchName);
        for (int i = 0; i < n; i++) {
            if (strcmp(emp[i].name, searchName) == 0) {
                printf("\nEmployee Found:\n");
                printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Employee not found.\n");
    }
}
void updateSalaries(struct Employee emp[], int n, float threshold) {
    for (int i = 0; i < n; i++) {
        if (emp[i].salary < threshold) {
            emp[i].salary = emp[i].salary * 1.10;
        }
    }
}
int main() {
    int n, choice;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    struct Employee employees[n];
    for (int i = 0; i < n; i++) {
        printf("Enter details for employee %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Name: ");
        scanf("%s", employees[i].name);
        printf("Designation: ");
        scanf("%s", employees[i].designation);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }
    while (1) {
        printf("\nMenu:\n");
        printf("1. Display all employees\n");
        printf("2. Find highest salary\n");
        printf("3. Search employee\n");
        printf("4. Update salaries below threshold\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayEmployees(employees, n);
                break;
            case 2:
                findHighestSalary(employees, n);
                break;
            case 3:
                printf("Search by:\n1. ID\n2. Name\n");
                int searchChoice;
                scanf("%d", &searchChoice);
                searchEmployee(employees, n, searchChoice);
                break;
            case 4:
                updateSalaries(employees, n, 50000.0);
                printf("Salaries updated.\n");
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
