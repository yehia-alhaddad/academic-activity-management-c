#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void ViewActivitiesWithPoints();
int countActivitiesWithPrefix();
int studentRole();
void ShowActivities();
void trimWhitespace(); 

//Structures
struct Activity {
    char code[20];
    char name[70];
    char type[20];
    float points;
};

typedef struct {
    char studentID[20];
    char activities[50][10];
    int activityCount;
} StudentDetails;

int main(){
    studentRole("S4033");
}
void addActivity(const char *studentID, const char *codeToAdd) {
    FILE *studentFile = fopen("StudentAccounts.txt", "r+");

    if (studentFile == NULL) {
        perror("Error opening student file");
        return;
    }

    StudentDetails studentDetails;
    int found = 0;

    // Read student's chosen activities
    while (fscanf(studentFile, "%19[^,],", studentDetails.studentID) == 1) {
        // Check if the student ID matches
        if (strcmp(studentDetails.studentID, studentID) == 0) {
            found = 1;
            studentDetails.activityCount = 0;

            // Read and store existing activities
            while (fscanf(studentFile, "%9[^;];", studentDetails.activities[studentDetails.activityCount]) == 1) {
                trimWhitespace(studentDetails.activities[studentDetails.activityCount]);
                studentDetails.activityCount++;

                if (studentDetails.activityCount >= 50) {
                    printf("Warning: Maximum number of activities reached.\n");
                    break;
                }
            }

            // Add the new activity if not already present
            int activityFound = 0;
            for (int i = 0; i < studentDetails.activityCount; i++) {
                if (strcmp(studentDetails.activities[i], codeToAdd) == 0) {
                    activityFound = 1;
                    break;
                }
            }

            if (!activityFound) {
                // Append the new activity code
                strncpy(studentDetails.activities[studentDetails.activityCount], codeToAdd, sizeof(studentDetails.activities[0]));
                studentDetails.activityCount++;

                // Move file pointer back to the beginning of the line
                fseek(studentFile, -strlen(studentDetails.studentID) - 1, SEEK_CUR);

                // Write updated activities to the file
                for (int i = 0; i < studentDetails.activityCount; i++) {
                    fprintf(studentFile, "%s;", studentDetails.activities[i]);
                }

                // Break out of the loop since we found and updated the student
                break;
            }
        }

        // Skip the rest of the line
        while (fgetc(studentFile) != '\n') {
            // Check for end of file
            if (feof(studentFile)) {
                break;
            }
        }
    }

    fclose(studentFile);

    if (!found) {
        printf("Student ID %s not found.\n", studentID);
    } else {
        printf("Activity code %s added to student %s.\n", codeToAdd, studentID);
    }
}

void deleteActivity(const char *studentID, const char *codeToDelete) {
    FILE *studentFile = fopen("StudentAccounts.txt", "r+");
    FILE *tempFile = fopen("tempfile.txt", "w");

    if (studentFile == NULL || tempFile == NULL) {
        perror("Error opening files");
        if (studentFile != NULL) fclose(studentFile);
        if (tempFile != NULL) fclose(tempFile);
        return;
    }

    StudentDetails students[50];
    int studentCount = 0;

    // Read each line in the file
    while (fscanf(studentFile, "%19[^,],", students[studentCount].studentID) == 1) {
        // Read and store existing activities
        students[studentCount].activityCount = 0;
        while (fscanf(studentFile, "%19[^;];", students[studentCount].activities[students[studentCount].activityCount]) == 1) {
            students[studentCount].activityCount++;
        }

        studentCount++;
    }

    // Process each student and rewrite the file
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, studentID) == 0) {
            fprintf(tempFile, "%s,", students[i].studentID);

            // Process existing activities
            int activitiesModified = 0;
            for (int j = 0; j < students[i].activityCount; j++) {
                // Check if the activity matches the one to delete and has the correct prefix
                if (strcmp(students[i].activities[j], codeToDelete) == 0) {
                    printf("Activity code %s deleted from student %s.\n", codeToDelete, students[i].studentID);
                    activitiesModified = 1;
                } else {
                    // Write other activities to temp file
                    fprintf(tempFile, "%s;", students[i].activities[j]);
                }
            }

            // Add newline at the end of the line if activities are modified
            if (activitiesModified) {
                fprintf(tempFile, "\n");
            }
        } else {
            // Copy the line as is to temp file
            fprintf(tempFile, "%s,", students[i].studentID);
            for (int j = 0; j < students[i].activityCount; j++) {
                fprintf(tempFile, "%s;", students[i].activities[j]);
            }
            fprintf(tempFile, "\n");
        }
    }

    fclose(studentFile);
    fclose(tempFile);

    // Rewrite the entire file with the contents of the temporary file
    FILE *tempFileRead = fopen("tempfile.txt", "r");
    FILE *studentFileWrite = fopen("StudentAccounts.txt", "w");

    if (tempFileRead == NULL || studentFileWrite == NULL) {
        perror("Error opening files");
        if (tempFileRead != NULL) fclose(tempFileRead);
        if (studentFileWrite != NULL) fclose(studentFileWrite);
        return;
    }

    char ch;
    while ((ch = fgetc(tempFileRead)) != EOF) {
        fputc(ch, studentFileWrite);
    }

    fclose(tempFileRead);
    fclose(studentFileWrite);

    // Remove the temporary file
    remove("tempfile.txt");
}


void trimWhitespace(char *str) {
    // Trim leading whitespaces
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // Trim trailing whitespaces
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    // Null-terminate the trimmed string
    *(end + 1) = '\0';
}


// Function to view any activity using the prefix code and their associated points
void ShowActivities() {
    FILE *file = fopen("ActivityCoord.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[100];

    while (fgets(line, sizeof(line), file)) {
        char code[10], name[50], type[20];
        float points;

        sscanf(line, "%[^;];%[^;];%[^;];%f;\n", code, name, type, &points);

        if (strncmp(code, "E", 1) == 0) {
            printf("Elective (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if (strncmp(code, "SM", 2) == 0) {
            printf("Specialise Module (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if (strncmp(code, "CM", 2) == 0) {
            printf("Core Module (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if (strncmp(code, "W", 1) == 0) {
            printf("Workshop (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if (strncmp(code, "T", 1) == 0) {
            printf("Talk (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if ((strncmp(code, "CS", 2) == 0 || strncmp(code, "PS", 2) == 0) && strstr(type, "Member")) {
            printf("Society Member (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if ((strncmp(code, "CS", 2) == 0 || strncmp(code, "PS", 2) == 0) && strstr(type, "Committee")) {
            printf("Society Committee (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if (strncmp(code, "PC", 2) == 0 && strstr(type, "Member")) {
            printf("Club Member (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if (strncmp(code, "PC", 2) == 0 && strstr(type, "Committee")) {
            printf("Club Committee (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        } else if (strncmp(code, "CT", 3) == 0) {
            printf("Competition (%s): %s - Type (%s) - Points: %.1f\n", code, name, type, points);
        }
    }

    fclose(file);
}


int countActivitiesWithPrefix(StudentDetails *studentDetails, const char *prefix) {
    int count = 0;
    for (int i = 0; i < studentDetails->activityCount; i++) {
        if (strncmp(studentDetails->activities[i], prefix, strlen(prefix)) == 0) {
            count++;
        }
    }
    return count;
}

void ViewActivitiesWithPoints(const char *studentID) {
    FILE *studentFile = fopen("StudentAccounts.txt", "r");
    FILE *activityFile = fopen("ActivityCoord.txt", "r");

    if (studentFile == NULL || activityFile == NULL) {
        perror("Error opening file");
        return;
    }

    char studentLine[256];
    char activityLine[100];

    StudentDetails studentDetails;

    // Read student's chosen activities
    while (fgets(studentLine, sizeof(studentLine), studentFile)) {
        char *token = strtok(studentLine, ",");
        if (token != NULL && strcmp(token, studentID) == 0) {
            // Found the student ID, now extract and tokenize the activity codes
            strcpy(studentDetails.studentID, token);
            studentDetails.activityCount = 0;
            char *activityToken = strtok(NULL, ";");
            while (activityToken != NULL) {
                // Store the activity code in the array after trimming whitespaces
                trimWhitespace(activityToken);
                strncpy(studentDetails.activities[studentDetails.activityCount], activityToken, sizeof(studentDetails.activities[0]));
                studentDetails.activityCount++;

                // Check if the array needs to be resized
                if (studentDetails.activityCount >= 50) {
                    printf("Warning: Maximum number of activities reached.\n");
                    break;
                }

                activityToken = strtok(NULL, ";");
            }
            break;
        }
    }

    float totalPointsCM = 0.0;
    float totalPointsOther = 0.0;
    int totalCreditsCM = 0;
    int totalCreditsOther = 0;

    // Display details about chosen activities
    for (int i = 0; i < studentDetails.activityCount; i++) {
        fseek(activityFile, 0, SEEK_SET); // Move to the beginning of the file
        while (fgets(activityLine, sizeof(activityLine), activityFile)) {
            struct Activity activity;
            sscanf(activityLine, "%[^;];%[^;];%[^;];%f\n", activity.code, activity.name, activity.type, &activity.points);

            // Trim whitespaces from the activity code for comparison
            trimWhitespace(activity.code);

            if (strcmp(studentDetails.activities[i], activity.code) == 0) {
                // Display detailed information about the activity
                printf("You have chosen activity code: %s\n", studentDetails.activities[i]);
                printf("Details: %s - Type: %s - Points: %.1f\n", activity.name, activity.type, activity.points);

                // Accumulate points and credits for the chosen activity
                if (strncmp(activity.code, "CM", 2) == 0) {
                    totalPointsCM += activity.points;
                    totalCreditsCM += (int)(activity.points / 10);
                } else {
                    totalPointsOther += activity.points;
                    totalCreditsOther += (int)(activity.points / 10);
                }
            }
        }
    }

    // Check if the student fulfills the requirement
    int coreModuleCount = countActivitiesWithPrefix(&studentDetails, "CM");
    int totalCredits = totalCreditsCM + totalCreditsOther;

    if (coreModuleCount == 4 && totalCredits >= 16 && totalCredits <= 20) {
        printf("Congratulations! You have fulfilled the requirements with 4 Core Modules and between 16 to 20 total credits.\n");
    } else {
        printf("You have not fulfilled the requirements.\n");
    }

    // Display total points and credits
    printf("Total Points (CM): %.1f\n", totalPointsCM);
    printf("Total Credits (CM): %d\n", totalCreditsCM);
    printf("Total Points (Other): %.1f\n", totalPointsOther);
    printf("Total Credits (Other): %d\n", totalCreditsOther);
    printf("Total Credits (Overall): %d\n", totalCredits);

    fclose(studentFile);
    fclose(activityFile);
}

int studentRole(const char ID[20]) {
    int choice;
    char codeToChange[20];
    char codeToAdd[20];
    char codeToDelete[20];
    int coreCredits = 0;
    int coreModulesSelected = 0; // Count of selected core modules

    do {
        printf("\nMenu:\n");
        printf("1. View/Track activities and credits\n");
        printf("2. Select an Core Module or an activity\n");
        printf("3. Delete an Core Module or an activity\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                ViewActivitiesWithPoints(ID); // Call the function to display credits and points
                break;
            case 2:
                ShowActivities();
                printf("Enter the code of the activity to add: ");
                scanf("%s", codeToAdd);
                while (getchar() != '\n'); // Clear input buffer
                // Add the activity to the list of chosen activities and also write it to Activity.txt
                addActivity(ID,codeToAdd);
                break;
            case 3:
                printf("Enter the code of the core module or the activity you want to delete: ");
                scanf("%s", codeToDelete);
                deleteActivity(ID, codeToDelete);
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}
