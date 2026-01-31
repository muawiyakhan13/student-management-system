#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[100];
    char className[50];
    int roll;
    double marks;
    int attendance;
};

/* Function Prototypes */
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void manageAttendance();
void generateReport();

/* ---------- ADD STUDENT ---------- */
void addStudent() {
    struct student s;
    FILE *fp = fopen("students.dat", "ab");
    if (!fp) {
        printf("File error!\n");
        return;
    }

    getchar(); // clear buffer
    printf("\nEnter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);
    getchar(); // clear newline after scanf

    printf("Enter Class: ");
    fgets(s.className, sizeof(s.className), stdin);
    s.className[strcspn(s.className, "\n")] = 0;

    printf("Enter Marks: ");
    scanf("%lf", &s.marks);

    s.attendance = 0; // initialize attendance

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

/* ---------- VIEW STUDENTS ---------- */
void viewStudents() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    struct student s;
    printf("\n--- STUDENTS RECORD ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll      : %d\nName      : %s\nClass     : %s\nMarks     : %.2lf\nAttendance: %d\n",
               s.roll, s.name, s.className, s.marks, s.attendance);
    }
    fclose(fp);
}

/* ---------- SEARCH STUDENT ---------- */
void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int roll, found = 0;
    printf("\nEnter Roll No to search: ");
    scanf("%d", &roll);

    struct student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\n--- STUDENT FOUND ---\n");
            printf("Roll      : %d\nName      : %s\nClass     : %s\nMarks     : %.2lf\nAttendance: %d\n",
                   s.roll, s.name, s.className, s.marks, s.attendance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

/* ---------- UPDATE STUDENT ---------- */
void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int roll, found = 0;
    printf("\nEnter Roll No to update: ");
    scanf("%d", &roll);

    struct student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            getchar(); // clear buffer

            printf("Enter new Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter new Class: ");
            fgets(s.className, sizeof(s.className), stdin);
            s.className[strcspn(s.className, "\n")] = 0;

            printf("Enter new Marks: ");
            scanf("%lf", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("Student updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

/* ---------- DELETE STUDENT ---------- */
void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int roll, found = 0;
    printf("\nEnter Roll No to delete: ");
    scanf("%d", &roll);

    struct student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll)
            fwrite(&s, sizeof(s), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found!\n");
}

/* ---------- MANAGE ATTENDANCE ---------- */
void manageAttendance() {
    FILE *fp = fopen("students.dat", "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int roll, found = 0;
    printf("\nEnter Roll No to update Attendance: ");
    scanf("%d", &roll);

    struct student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("Enter new Attendance: ");
            scanf("%d", &s.attendance);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("Attendance updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

/* ---------- GENERATE REPORT ---------- */
void generateReport() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    struct student s;
    printf("\n--- STUDENT REPORT ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Class: %s | Marks: %.2lf | Attendance: %d\n",
               s.roll, s.name, s.className, s.marks, s.attendance);
    }
    fclose(fp);
}

/* ---------- MAIN ---------- */
int main() {
    int choice;
    do {
        printf("\n--- SCHOOL MANAGEMENT SYSTEM ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Manage Attendance\n");
        printf("7. Generate Report\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: manageAttendance(); break;
            case 7: generateReport(); break;
            case 8: printf("Exiting program. Thank you!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }

    } while (choice != 8);

    return 0;
}
