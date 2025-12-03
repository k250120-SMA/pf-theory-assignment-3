#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char registrationDate[11];
    char dateOfBirth[11];
    char interest[10];
} Student;

Student *database = NULL;
int recordCount = 0;
int databaseCapacity = 10;
const char *filename = "members.dat";

void loadDatabase() {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Creating new database file...\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    recordCount = fileSize / sizeof(Student);
    
    if (database == NULL) {
        database = (Student *)malloc(recordCount * sizeof(Student));
        databaseCapacity = recordCount;
    } else {
        Student *temp = (Student *)realloc(database, recordCount * sizeof(Student));
        if (temp != NULL) {
            database = temp;
            databaseCapacity = recordCount;
        }
    }
    
    if (database != NULL) {
        fread(database, sizeof(Student), recordCount, file);
        printf("Loaded %d student records from file.\n", recordCount);
    } else {
        printf("Memory allocation failed while loading database.\n");
        recordCount = 0;
    }
    
    fclose(file);
}

void saveDatabase() {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file for writing.\n");
        return;
    }
    
    fwrite(database, sizeof(Student), recordCount, file);
    fclose(file);
    printf("Database saved successfully with %d records.\n", recordCount);
}

int isDuplicateID(int studentID) {
    for (int i = 0; i < recordCount; i++) {
        if (database[i].studentID == studentID) {
            return 1;
        }
    }
    return 0;
}

void addStudent() {
    if (recordCount >= databaseCapacity) {
        databaseCapacity += 10;
        Student *temp = (Student *)realloc(database, databaseCapacity * sizeof(Student));
        if (temp == NULL) {
            printf("Memory allocation failed. Cannot add student.\n");
            return;
        }
        database = temp;
    }
    
    Student newStudent;
    
    printf("\n=== REGISTER NEW STUDENT ===\n");
    
    do {
        printf("Enter Student ID (unique): ");
        scanf("%d", &newStudent.studentID);
        getchar();
        
        if (isDuplicateID(newStudent.studentID)) {
            printf("Error: Student ID already exists. Please enter a unique ID.\n");
        }
    } while (isDuplicateID(newStudent.studentID));
    
    printf("Enter Full Name: ");
    fgets(newStudent.fullName, sizeof(newStudent.fullName), stdin);
    newStudent.fullName[strcspn(newStudent.fullName, "\n")] = '\0';
    
    int batchChoice;
    printf("Select Batch:\n");
    printf("1. Computer Science (CS)\n");
    printf("2. Software Engineering (SE)\n");
    printf("3. Cyber Security\n");
    printf("4. Artificial Intelligence (AI)\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &batchChoice);
    getchar();
    
    switch (batchChoice) {
        case 1: strcpy(newStudent.batch, "CS"); break;
        case 2: strcpy(newStudent.batch, "SE"); break;
        case 3: strcpy(newStudent.batch, "Cyber Security"); break;
        case 4: strcpy(newStudent.batch, "AI"); break;
        default: strcpy(newStudent.batch, "CS"); break;
    }
    
    int memChoice;
    printf("Select Membership Type:\n");
    printf("1. IEEE\n");
    printf("2. ACM\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &memChoice);
    getchar();
    strcpy(newStudent.membershipType, (memChoice == 1) ? "IEEE" : "ACM");
    
    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(newStudent.registrationDate, sizeof(newStudent.registrationDate), stdin);
    newStudent.registrationDate[strcspn(newStudent.registrationDate, "\n")] = '\0';
    
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(newStudent.dateOfBirth, sizeof(newStudent.dateOfBirth), stdin);
    newStudent.dateOfBirth[strcspn(newStudent.dateOfBirth, "\n")] = '\0';
    
    int interestChoice;
    printf("Select Interest:\n");
    printf("1. IEEE\n");
    printf("2. ACM\n");
    printf("3. Both\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &interestChoice);
    getchar();
    
    switch (interestChoice) {
        case 1: strcpy(newStudent.interest, "IEEE"); break;
        case 2: strcpy(newStudent.interest, "ACM"); break;
        case 3: strcpy(newStudent.interest, "Both"); break;
        default: strcpy(newStudent.interest, "Both"); break;
    }
    
    database[recordCount] = newStudent;
    recordCount++;
    
    saveDatabase();
    printf("Student registered successfully!\n");
}

void updateStudent() {
    int studentID, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &studentID);
    getchar();
    
    for (int i = 0; i < recordCount; i++) {
        if (database[i].studentID == studentID) {
            found = 1;
            printf("\n=== UPDATE STUDENT INFORMATION ===\n");
            printf("Current Record:\n");
            printf("Name: %s\n", database[i].fullName);
            printf("Batch: %s\n", database[i].batch);
            printf("Membership: %s\n", database[i].membershipType);
            
            int choice;
            printf("\nWhat would you like to update?\n");
            printf("1. Batch\n");
            printf("2. Membership Type\n");
            printf("3. Interest\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            getchar();
            
            switch (choice) {
                case 1:
                    printf("Select New Batch:\n");
                    printf("1. Computer Science (CS)\n");
                    printf("2. Software Engineering (SE)\n");
                    printf("3. Cyber Security\n");
                    printf("4. Artificial Intelligence (AI)\n");
                    printf("Enter choice (1-4): ");
                    scanf("%d", &choice);
                    getchar();
                    switch (choice) {
                        case 1: strcpy(database[i].batch, "CS"); break;
                        case 2: strcpy(database[i].batch, "SE"); break;
                        case 3: strcpy(database[i].batch, "Cyber Security"); break;
                        case 4: strcpy(database[i].batch, "AI"); break;
                    }
                    break;
                    
                case 2:
                    printf("Select New Membership Type:\n");
                    printf("1. IEEE\n");
                    printf("2. ACM\n");
                    printf("Enter choice (1-2): ");
                    scanf("%d", &choice);
                    getchar();
                    strcpy(database[i].membershipType, (choice == 1) ? "IEEE" : "ACM");
                    break;
                    
                case 3:
                    printf("Select New Interest:\n");
                    printf("1. IEEE\n");
                    printf("2. ACM\n");
                    printf("3. Both\n");
                    printf("Enter choice (1-3): ");
                    scanf("%d", &choice);
                    getchar();
                    switch (choice) {
                        case 1: strcpy(database[i].interest, "IEEE"); break;
                        case 2: strcpy(database[i].interest, "ACM"); break;
                        case 3: strcpy(database[i].interest, "Both"); break;
                    }
                    break;
                    
                default:
                    printf("Invalid choice.\n");
                    return;
            }
            
            saveDatabase();
            printf("Student information updated successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", studentID);
    }
}

void deleteStudent() {
    int studentID, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &studentID);
    getchar();
    
    for (int i = 0; i < recordCount; i++) {
        if (database[i].studentID == studentID) {
            found = 1;
            for (int j = i; j < recordCount - 1; j++) {
                database[j] = database[j + 1];
            }
            recordCount--;
            
            saveDatabase();
            printf("Student with ID %d deleted successfully.\n", studentID);
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", studentID);
    }
}

void displayAllStudents() {
    printf("\n=== ALL STUDENT REGISTRATIONS ===\n");
    printf("===========================================================================================================\n");
    printf("ID\tName\t\t\tBatch\t\tMembership\tReg Date\tDOB\t\tInterest\n");
    printf("===========================================================================================================\n");
    
    if (recordCount == 0) {
        printf("No student records found.\n");
        return;
    }
    
    for (int i = 0; i < recordCount; i++) {
        printf("%d\t%-20s\t%-10s\t%-10s\t%s\t%s\t%s\n",
               database[i].studentID,
               database[i].fullName,
               database[i].batch,
               database[i].membershipType,
               database[i].registrationDate,
               database[i].dateOfBirth,
               database[i].interest);
    }
    printf("===========================================================================================================\n");
    printf("Total Records: %d\n", recordCount);
}

void generateBatchReport() {
    char selectedBatch[20];
    int batchChoice;
    
    printf("\n=== GENERATE BATCH REPORT ===\n");
    printf("Select Batch:\n");
    printf("1. Computer Science (CS)\n");
    printf("2. Software Engineering (SE)\n");
    printf("3. Cyber Security\n");
    printf("4. Artificial Intelligence (AI)\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &batchChoice);
    getchar();
    
    switch (batchChoice) {
        case 1: strcpy(selectedBatch, "CS"); break;
        case 2: strcpy(selectedBatch, "SE"); break;
        case 3: strcpy(selectedBatch, "Cyber Security"); break;
        case 4: strcpy(selectedBatch, "AI"); break;
        default: printf("Invalid choice.\n"); return;
    }
    
    printf("\n=== %s BATCH REPORT ===\n", selectedBatch);
    printf("================================================================================================\n");
    printf("ID\tName\t\t\tMembership\tInterest\n");
    printf("================================================================================================\n");
    
    int count = 0;
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(database[i].batch, selectedBatch) == 0) {
            printf("%d\t%-20s\t%-10s\t%s\n",
                   database[i].studentID,
                   database[i].fullName,
                   database[i].membershipType,
                   database[i].interest);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No students found in %s batch.\n", selectedBatch);
    } else {
        printf("================================================================================================\n");
        printf("Total %s students: %d\n", selectedBatch, count);
    }
}

void freeMemory() {
    if (database != NULL) {
        free(database);
        database = NULL;
    }
    recordCount = 0;
    databaseCapacity = 0;
}

int main() {
    printf("=== FAST UNIVERSITY MEMBERSHIP REGISTRATION SYSTEM ===\n");
    printf("=== IEEE & ACM Student Chapters ===\n\n");
    
    database = (Student *)malloc(databaseCapacity * sizeof(Student));
    if (database == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }
    
    loadDatabase();
    
    int choice;
    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Register New Student\n");
        printf("2. Update Student Information\n");
        printf("3. Delete Student Registration\n");
        printf("4. View All Registrations\n");
        printf("5. Generate Batch Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: displayAllStudents(); break;
            case 5: generateBatchReport(); break;
            case 6: 
                printf("Saving database...\n");
                saveDatabase();
                freeMemory();
                printf("Thank you for using the system. Goodbye!\n");
                break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
