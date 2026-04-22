#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum constants of arrays
#define MAX_STUDENTS 100
#define MAX_ACTIVITIES 50

// Define a structure of Activities
struct Activity {
    char code[20];
    char name[70];
    char type[20];
    float points;
};

// Define a structure of StudentDetails
typedef struct {
    char studentID[20];
    char activities[MAX_ACTIVITIES][10];
    int activityCount;
} StudentDetails;


void handleError(const char *errorMessage);
void loadStudentData(StudentDetails students[], int *studentCount);
void loadActivityData(struct Activity activities[], int *activityCount);
void generateStudentReports(StudentDetails students[], int studentCount, struct Activity activities[], int activityCount);
void trackStudentActivity(StudentDetails students[], int studentCount, struct Activity activities[], int activityCount);


int main() {
    struct Activity activities[MAX_ACTIVITIES];
    int activityCount = 0;

    StudentDetails students[MAX_STUDENTS];
    int studentCount = 0;

    loadActivityData(activities, &activityCount);
    loadStudentData(students, &studentCount);

    int choice;
    printf("1. Generate Student Reports\n");
    printf("2. Track Student Activity\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            generateStudentReports(students, studentCount, activities, activityCount);
            break;
        case 2: {
            trackStudentActivity(students, studentCount, activities, activityCount);
            break;
        }
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

// Function handling errors and displaying messages
void handleError(const char *errorMessage) {
    printf("Error: %s\n", errorMessage);
    exit(1);
}

// Function to load student data from a file
void loadStudentData(StudentDetails students[], int *studentCount) {
    FILE *studentFile = fopen("StudentAccounts.txt", "r");
    if (studentFile == NULL) {
        handleError("Failed to open StudentAccounts.txt. Make sure the file exists and is accessible.");
    }

    *studentCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), studentFile) != NULL) {
        char *token = strtok(line, ",");
        strcpy(students[*studentCount].studentID, token);
        students[*studentCount].activityCount = 0;

        token = strtok(NULL, ";");
        while (token != NULL) {
            strcpy(students[*studentCount].activities[students[*studentCount].activityCount], token);
            students[*studentCount].activityCount++;
            token = strtok(NULL, ";");
        }

        (*studentCount)++;
    }

    fclose(studentFile);
}

// Function to load activity data from a file
void loadActivityData(struct Activity activities[], int *activityCount) {
    FILE *activityFile = fopen("activitycoord.txt", "r");
    if (activityFile == NULL) {
        handleError("Failed to open ActivityCoord.txt. Make sure the file exists and is accessible.");
    }

    *activityCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), activityFile) != NULL) {
        char *token = strtok(line, ";");
        strcpy(activities[*activityCount].code, token);
        token = strtok(NULL, ";");
        strcpy(activities[*activityCount].name, token);
        token = strtok(NULL, ";");
        strcpy(activities[*activityCount].type, token);
        token = strtok(NULL, ";");
        sscanf(token, "%f", &activities[*activityCount].points);
        (*activityCount)++;
    }

    fclose(activityFile);
}

// Function to generate student reports
void generateStudentReports(StudentDetails students[], int studentCount, struct Activity activities[], int activityCount) {
    int choice;
    do {
        printf("\nChoose an option:\n");
        printf("1. Show reports for all students\n");
        printf("2. Show reports for a specific student\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Show reports for all students
                for (int i = 0; i < studentCount; i++) {
                    printf("Student ID: %s\n", students[i].studentID);
                    printf("Chosen Activities:\n");
                    float totalPoints = 0.0;
                    int coreModuleCount = 0;
                    int electiveCount = 0;
                    int workshopCount = 0;
                    int talkCount = 0;
                    int societyMemberCount = 0;
                    int societyCommitteeCount = 0;
                    int clubMemberCount = 0;
                    int clubCommitteeCount = 0;
                    int competitionCount = 0;
                    int totalCredits = 0;

                    for (int j = 0; j < students[i].activityCount; j++) {
                        printf(" - %s\n", students[i].activities[j]);

                        // Calculate total points, core modules, elective modules, and total credits
                        for (int k = 0; k < activityCount; k++) {
                            if (strcmp(students[i].activities[j], activities[k].code) == 0) {
                                totalPoints += activities[k].points;

                                // Categorize activities based on type
                                if (strncmp(activities[k].code, "CM", 2) == 0) {
                                    coreModuleCount++;
                                } else if (strncmp(activities[k].code, "E", 1) == 0) {
                                    electiveCount++;
                                } else if (strncmp(activities[k].code, "W", 1) == 0) {
                                    workshopCount++;
                                } else if (strncmp(activities[k].code, "T", 1) == 0) {
                                    talkCount++;
                                } else if (strncmp(activities[k].code, "CS", 2) == 0 && strstr(activities[k].name, "Member")) {
                                    societyMemberCount++;
                                } else if (strncmp(activities[k].code, "CS", 2) == 0 && strstr(activities[k].name, "Committee")) {
                                    societyCommitteeCount++;
                                } else if (strncmp(activities[k].code, "PC", 2) == 0 && strstr(activities[k].name, "Member")) {
                                    clubMemberCount++;
                                } else if (strncmp(activities[k].code, "PC", 2) == 0 && strstr(activities[k].name, "Committee")) {
                                    clubCommitteeCount++;
                                } else if (strncmp(activities[k].code, "CT", 2) == 0) {
                                    competitionCount++;
                                }

                                totalCredits += (int)(activities[k].points / 10);
                                break;
                            }
                        }
                    }

                    printf("Total Points: %.1f\n", totalPoints);
                    printf("Core Modules Taken: %d\n", coreModuleCount);
                    printf("Elective Modules Taken: %d\n", electiveCount);
                    printf("Workshops Taken: %d\n", workshopCount);
                    printf("Talks Taken: %d\n", talkCount);
                    printf("Society Member Activities: %d\n", societyMemberCount);
                    printf("Society Committee Activities: %d\n", societyCommitteeCount);
                    printf("Club Member Activities: %d\n", clubMemberCount);
                    printf("Club Committee Activities: %d\n", clubCommitteeCount);
                    printf("Competition Activities: %d\n", competitionCount);
                    printf("Total Credits: %d\n", totalCredits);

                    // Additional report logic can be added here

                    printf("\n");
                }
                break;
            case 2: {
                // Show reports for a specific student
                char studentID[20];
                printf("Enter student ID: ");
                scanf("%s", studentID);
                int studentIndex = -1; // Initialize to an invalid index
                for (int i = 0; i < studentCount; i++) {
                    if (strcmp(studentID, students[i].studentID) == 0) {
                        studentIndex = i; // Store the index of the found student
                        break;
                    }
                }

                if (studentIndex == -1) {
                    printf("Student ID not found.\n");
                } else {
                    // Display reports for the specific student (similar to the code in case 1)
                    printf("Student ID: %s\n", students[studentIndex].studentID);
                    printf("Chosen Activities:\n");
                    float totalPoints = 0.0;
                    int coreModuleCount = 0;
                    int electiveCount = 0;
                    int workshopCount = 0;
                    int talkCount = 0;
                    int societyMemberCount = 0;
                    int societyCommitteeCount = 0;
                    int clubMemberCount = 0;
                    int clubCommitteeCount = 0;
                    int competitionCount = 0;
                    int totalCredits = 0;

                    for (int j = 0; j < students[studentIndex].activityCount; j++) {
                        printf(" - %s\n", students[studentIndex].activities[j]);

                        // Calculate total points, core modules, elective modules, and total credits
                        for (int k = 0; k < activityCount; k++) {
                            if (strcmp(students[studentIndex].activities[j], activities[k].code) == 0) {
                                totalPoints += activities[k].points;

                                // Categorize activities based on type
                                if (strncmp(activities[k].code, "CM", 2) == 0) {
                                    coreModuleCount++;
                                } else if (strncmp(activities[k].code, "E", 1) == 0) {
                                    electiveCount++;
                                } else if (strncmp(activities[k].code, "W", 1) == 0) {
                                    workshopCount++;
                                } else if (strncmp(activities[k].code, "T", 1) == 0) {
                                    talkCount++;
                                } else if (strncmp(activities[k].code, "CS", 2) == 0 && strstr(activities[k].name, "Member")) {
                                    societyMemberCount++;
                                } else if (strncmp(activities[k].code, "CS", 2) == 0 && strstr(activities[k].name, "Committee")) {
                                    societyCommitteeCount++;
                                } else if (strncmp(activities[k].code, "PC", 2) == 0 && strstr(activities[k].name, "Member")) {
                                    clubMemberCount++;
                                } else if (strncmp(activities[k].code, "PC", 2) == 0 && strstr(activities[k].name, "Committee")) {
                                    clubCommitteeCount++;
                                } else if (strncmp(activities[k].code, "CT", 2) == 0) {
                                    competitionCount++;
                                }

                                totalCredits += (int)(activities[k].points / 10);
                                break;
                            }
                        }
                    }

                    printf("Total Points: %.1f\n", totalPoints);
                    printf("Core Modules Taken: %d\n", coreModuleCount);
                    printf("Elective Modules Taken: %d\n", electiveCount);
                    printf("Workshops Taken: %d\n", workshopCount);
                    printf("Talks Taken: %d\n", talkCount);
                    printf("Society Member Activities: %d\n", societyMemberCount);
                    printf("Society Committee Activities: %d\n", societyCommitteeCount);
                    printf("Club Member Activities: %d\n", clubMemberCount);
                    printf("Club Committee Activities: %d\n", clubCommitteeCount);
                    printf("Competition Activities: %d\n", competitionCount);
                    printf("Total Credits: %d\n", totalCredits);

                    // Additional report logic can be added here

                    printf("\n");
                }
                break;
            }
            case 3:
                // Exit the menu
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

// Function to track and display detailed student activity
void trackStudentActivity(StudentDetails students[], int studentCount, struct Activity activities[], int activityCount) {
    char studentID[20];
    float totalPoints = 0.0;
    int totalCredits = 0;
    int societyMemberCount = 0;
    int societyCommitteeCount = 0;
    int coreModuleCount = 0;
    int electiveCount = 0;            
    int societyMemberCount = 0;
    int societyCommitteeCount = 0;
    int clubMemberCount = 0;
    int clubCommitteeCount = 0;
    int competitionCount = 0;
    printf("Enter student ID: ");
    scanf("%s", studentID);

    int studentIndex = -1; // Initialize to an invalid index
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(studentID, students[i].studentID) == 0) {
            studentIndex = i; // Store the index of the found student
            break;
        }
    }

    if (studentIndex == -1) {
        printf("Student ID not found.\n");
        return;
    }

    // Now that we have the student index, we can display a menu for the user
    int choice;
    do {
        printf("\nStudent ID: %s\n", students[studentIndex].studentID);
        printf("Chosen Activities:\n");

        for (int j = 0; j < students[studentIndex].activityCount; j++) {
            printf(" - %s\n", students[studentIndex].activities[j]);
        }

        printf("\nChoose an option:\n");
        printf("1. Show total points and credits\n");
        printf("2. Show core and elective module counts\n");
        printf("3. Show activity type counts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Calculate and display total points and credits

                for (int j = 0; j < students[studentIndex].activityCount; j++) {
                    for (int k = 0; k < activityCount; k++) {
                        if (strcmp(students[studentIndex].activities[j], activities[k].code) == 0) {
                            totalPoints += activities[k].points;
                            totalCredits += (int)(activities[k].points / 10);
                            break;
                        }
                    }
                }

                printf("Total Points: %.1f\n", totalPoints);
                printf("Total Credits: %d\n", totalCredits);
                break;
            case 2:
                // Calculate and display core and elective module counts

                for (int j = 0; j < students[studentIndex].activityCount; j++) {
                    for (int k = 0; k < activityCount; k++) {
                        if (strcmp(students[studentIndex].activities[j], activities[k].code) == 0) {
                            if (strncmp(activities[k].code, "CM", 2) == 0) {
                                coreModuleCount++;
                            } else if (strncmp(activities[k].code, "E", 1) == 0) {
                                electiveCount++;
                            }
                            break;
                        }
                    }
                }

                printf("Core Modules Taken: %d\n", coreModuleCount);
                printf("Elective Modules Taken: %d\n", electiveCount);
                break;
            case 3:
                // Calculate and display activity type counts

                for (int j = 0; j < students[studentIndex].activityCount; j++) {
                    for (int k = 0; k < activityCount; k++) {
                        if (strcmp(students[studentIndex].activities[j], activities[k].code) == 0) {
                            if (strncmp(activities[k].code, "CS", 2) == 0 && strstr(activities[k].name, "Member")) {
                                societyMemberCount++;
                            } else if (strncmp(activities[k].code, "CS", 2) == 0 && strstr(activities[k].name, "Committee")) {
                                societyCommitteeCount++;
                            } else if (strncmp(activities[k].code, "PC", 2) == 0 && strstr(activities[k].name, "Member")) {
                                clubMemberCount++;
                            } else if (strncmp(activities[k].code, "PC", 2) == 0 && strstr(activities[k].name, "Committee")) {
                                clubCommitteeCount++;
                            } else if (strncmp(activities[k].code, "CT", 2) == 0) {
                                competitionCount++;
                            }
                        }
                    }
                }

                printf("Society Member Activities: %d\n", societyMemberCount);
                printf("Society Committee Activities: %d\n", societyCommitteeCount);
                printf("Club Member Activities: %d\n", clubMemberCount);
                printf("Club Committee Activities: %d\n", clubCommitteeCount);
                printf("Competition Activities: %d\n", competitionCount);
                break;
            case 4:
                // Exit the menu
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}


int programLeader() {
    struct Activity activities[50];
    int activityCount = 0;

    StudentDetails students[50];
    int studentCount = 0;

    loadActivityData(activities, &activityCount);
    loadStudentData(students, &studentCount);

    int choice;
    printf("1. Generate Student Reports\n");
    printf("2. Track Student Activity\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            generateStudentReports(students, studentCount, activities, activityCount);
            break;
        case 2: {
            trackStudentActivity(students, studentCount, activities, activityCount);
            break;
        }
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}