/*
 * MINI PROJECT: Student Management System
 * Language: C
 * Description: A console-based application to manage student records.
 * Features: Add, View, Search, Update, Delete student records, and save/load
 *           data to/from a file (persistent storage).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define FILE_NAME "students.dat"

typedef struct {
    int roll;
    char name[NAME_LEN];
    float marks;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

/* ---------- Function Prototypes ---------- */
void loadFromFile();
void saveToFile();
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
int findIndexByRoll(int roll);
void pause_();

/* ---------- Main Menu ---------- */
int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student (by Roll No)\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Save & Exit\n");
        printf("======================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n'); /* clear bad input */
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                saveToFile();
                printf("Data saved. Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

/* ---------- Utility ---------- */
void pause_() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar();
}

int findIndexByRoll(int roll) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].roll == roll)
            return i;
    }
    return -1;
}

/* ---------- File Handling ---------- */
void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        return; /* No existing file, start fresh */
    }
    fread(&studentCount, sizeof(int), 1, fp);
    fread(students, sizeof(Student), studentCount, fp);
    fclose(fp);
    printf("Loaded %d student record(s) from file.\n", studentCount);
}

void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), studentCount, fp);
    fclose(fp);
}

/* ---------- Core Features ---------- */
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full!\n");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    if (findIndexByRoll(s.roll) != -1) {
        printf("A student with this roll number already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    students[studentCount++] = s;
    printf("Student added successfully!\n");

    saveToFile();
}

void viewStudents() {
    if (studentCount == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-10d %-30s %-10.2f\n",
               students[i].roll, students[i].name, students[i].marks);
    }
}

void searchStudent() {
    int roll;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    int idx = findIndexByRoll(roll);
    if (idx == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("\nRecord Found:\n");
    printf("Roll No : %d\n", students[idx].roll);
    printf("Name    : %s\n", students[idx].name);
    printf("Marks   : %.2f\n", students[idx].marks);
}

void updateStudent() {
    int roll;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    int idx = findIndexByRoll(roll);
    if (idx == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Enter new Name: ");
    scanf(" %49[^\n]", students[idx].name);

    printf("Enter new Marks: ");
    scanf("%f", &students[idx].marks);

    printf("Student record updated successfully!\n");
    saveToFile();
}

void deleteStudent() {
    int roll;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    int idx = findIndexByRoll(roll);
    if (idx == -1) {
        printf("Student not found!\n");
        return;
    }

    for (int i = idx; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;

    printf("Student record deleted successfully!\n");
    saveToFile();
}
