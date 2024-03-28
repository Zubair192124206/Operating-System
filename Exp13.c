#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee.dat"
#define MAX_NAME_LENGTH 50
#define MAX_RECORDS 100

struct Employee {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
};

void addRecord(FILE *fp) {
    struct Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);
    
    fseek(fp, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, fp);
    printf("Record added successfully.\n");
}

void displayRecord(FILE *fp, int id) {
    struct Employee emp;
    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, fp);
    printf("Employee ID: %d\n", emp.id);
    printf("Employee Name: %s\n", emp.name);
    printf("Employee Salary: %.2f\n", emp.salary);
}

void updateRecord(FILE *fp, int id) {
    struct Employee emp;
    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, fp);

    printf("Enter new name: ");
    scanf("%s", emp.name);
    printf("Enter new salary: ");
    scanf("%f", &emp.salary);

    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, fp);
    printf("Record updated successfully.\n");
}

void deleteRecord(FILE *fp, int id) {
    struct Employee emp;
    emp.id = 0;
    strcpy(emp.name, "");
    emp.salary = 0.0;

    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, fp);
    printf("Record deleted successfully.\n");
}

int main() {
    FILE *fp;
    int choice, id;

    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        fp = fopen(FILENAME, "wb+");
        if (fp == NULL) {
            printf("Error in opening file.\n");
            exit(1);
        }
    }

    while (1) {
        printf("\nEmployee Database Management\n");
        printf("1. Add Record\n");
        printf("2. Display Record\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(fp);
                break;
            case 2:
                printf("Enter employee ID: ");
                scanf("%d", &id);
                displayRecord(fp, id);
                break;
            case 3:
                printf("Enter employee ID: ");
                scanf("%d", &id);
                updateRecord(fp, id);
                break;
            case 4:
                printf("Enter employee ID: ");
                scanf("%d", &id);
                deleteRecord(fp, id);
                break;
            case 5:
                fclose(fp);
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

