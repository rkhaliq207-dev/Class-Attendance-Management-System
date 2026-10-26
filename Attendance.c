#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAYS 7

// Student structure (Linked List Node)
struct Student {
    int rollNo;
    char name[50];
    int attendance[DAYS];
    struct Student *next;
};

// Function declarations
void addStudent(struct Student **head);
void markAttendance(struct Student *head);
void displayStudents(struct Student *head);
void searchStudent(struct Student *head);
void deleteStudent(struct Student **head);
void freeList(struct Student *head);

int main() {
    struct Student *head = NULL;
    int choice;

    do {
        printf("\n===== CLASS ATTENDANCE MANAGER =====\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. Display Students\n");
        printf("4. Search Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&head);
                break;

            case 2:
                markAttendance(head);
                break;

            case 3:
                displayStudents(head);
                break;

            case 4:
                searchStudent(head);
                break;

            case 5:
                deleteStudent(&head);
                break;

            case 6:
                freeList(head);
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}

// Add Student
void addStudent(struct Student **head) {
    struct Student *newStudent;
    struct Student *temp;

    newStudent = malloc(sizeof(struct Student));

    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &newStudent->rollNo);

    // Check duplicate roll number
    temp = *head;
    while (temp != NULL) {
        if (temp->rollNo == newStudent->rollNo) {
            printf("Roll number already exists!\n");
            free(newStudent);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", newStudent->name);

    for (int i = 0; i < DAYS; i++) {
        newStudent->attendance[i] = 0;
    }

    newStudent->next = *head;
    *head = newStudent;

    printf("\nStudent added successfully!\n");
}

// Mark Attendance
void markAttendance(struct Student *head) {
    int roll, value;
    struct Student *temp = head;

    if (head == NULL) {
        printf("\nNo students available!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    while (temp != NULL) {
        if (temp->rollNo == roll) {

            printf("\nEnter attendance for 7 days:\n");
            printf("1 = Present, 0 = Absent\n");

            for (int i = 0; i < DAYS; i++) {
                do {
                    printf("Day %d: ", i + 1);
                    scanf("%d", &value);

                    if (value != 0 && value != 1) {
                        printf("Enter only 0 or 1!\n");
                    }
                } while (value != 0 && value != 1);

                temp->attendance[i] = value;
            }

            printf("\nAttendance recorded successfully!\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nStudent not found!\n");
}

// Display Students
void displayStudents(struct Student *head) {
    struct Student *temp = head;
    int present;
    float percentage;

    if (head == NULL) {
        printf("\nNo students available!\n");
        return;
    }

    printf("\n===== ATTENDANCE REPORT =====\n");

    while (temp != NULL) {
        present = 0;

        for (int i = 0; i < DAYS; i++) {
            if (temp->attendance[i] == 1) {
                present++;
            }
        }

        percentage = (present * 100.0) / DAYS;

        printf("\nRoll Number: %d", temp->rollNo);
        printf("\nName: %s", temp->name);

        printf("\nAttendance: ");
        for (int i = 0; i < DAYS; i++) {
            printf("%d ", temp->attendance[i]);
        }

        printf("\nPresent: %d/%d", present, DAYS);
        printf("\nAbsent: %d/%d", DAYS - present, DAYS);
        printf("\nPercentage: %.2f%%", percentage);

        if (percentage >= 75)
            printf("\nStatus: Sufficient\n");
        else
            printf("\nStatus: Low\n");

        printf("----------------------------\n");

        temp = temp->next;
    }
}

// Search Student
void searchStudent(struct Student *head) {
    int roll;
    struct Student *temp = head;

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            printf("\nStudent Found!\n");
            printf("Roll Number: %d\n", temp->rollNo);
            printf("Name: %s\n", temp->name);
            return;
        }

        temp = temp->next;
    }

    printf("\nStudent not found!\n");
}

// Delete Student
void deleteStudent(struct Student **head) {
    int roll;
    struct Student *temp = *head;
    struct Student *previous = NULL;

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    while (temp != NULL) {
        if (temp->rollNo == roll) {

            if (previous == NULL) {
                *head = temp->next;
            } else {
                previous->next = temp->next;
            }

            free(temp);
            printf("\nStudent deleted successfully!\n");
            return;
        }

        previous = temp;
        temp = temp->next;
    }

    printf("\nStudent not found!\n");
}

// Free allocated memory
void freeList(struct Student *head) {
    struct Student *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
