#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Mohammed Rasheed Yehia AL Haddad TP072509
void displayTitle();
void mainMenu();
bool login();
void registration();
void admin();
void afterRegistration();
void invalidChoice();
char* generateRandomStudentID();
int studentRole();
int CopyingCodesOfCoreModulesToStudentFiles();
int CopyingActivityCodesToStudentFile();
void deleteRowFromFile();
int TokenizeStudentsFiles();
void programLeader();
void activityMenu();
int programCoord();
void ManageUsers();
void deleteUser();
void updateUser();
void invalidChoice();
void registration();
void admin();
char* generateRandomStudentID();
int countActivitiesWithPrefix();
void ViewActivitiesWithPoints();
void trimWhitespace();
void addActivityCode();
void addActivityToStudent();

// Constants
const char ADMIN_USERNAME[] = "YhwachBach";
const char ADMIN_PASSWORD[] = "ZeAlmighty";
char Student[20];

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

int main() {
    srand(time(NULL));
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    printf("Welcome to the Login System\n");
    printf("============================\n\n");
    printf("1. LOGIN\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (login()) {
            } else {
                printf("Invalid username, password, or account type\n\n");
                printf("1. Try again\n");
                printf("2. Exit\n");
                printf("Enter your choice: ");
                int n2;
                scanf("%d", &n2);
                switch (n2) {
                    case 1:
                        login();
                        break;
                    case 2:
                        exit(0);
                        break;
                    default:
                        invalidChoice();
                        break;
                }
            }
            break;
        case 2:
            exit(0);
            break;
        default:
            invalidChoice();
            break;
    }
}

bool login() {
    char username[20], password[20], accounttype[20], studentID[20], course[50], semester[10];
    char storedStudentID[20], storedUsername[20], storedPassword[20], storedAccountType[20];
    int choice;

    printf("Welcome to the login page!\n");
    printf("------------------------\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        admin();
        return true;
    }

    printf("Choose the type that your account is:\n");
    printf("1. Student\n");
    printf("2. Program Coordinator\n");
    printf("3. Program Leader\n");
    printf("Enter a number: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(accounttype, "Student");
            break;
        case 2:
            strcpy(accounttype, "Program Coordinator");
            break;
        case 3:
            strcpy(accounttype, "Program Leader");
            break;
        default:
            printf("Invalid Input. Please choose a number.\n");
            return false;
    }

    FILE *file = fopen("Login.txt", "r");

    if (file != NULL) {
        while (fscanf(file, "%19[^;];%19[^;];%19[^;];%19[^\n]\n", storedStudentID, storedUsername, storedPassword, storedAccountType) == 4) {
            if (strcmp(username, storedUsername) == 0 &&
                strcmp(password, storedPassword) == 0 &&
                strcmp(accounttype, storedAccountType) == 0) {
                fclose(file);
                if (strcmp(storedAccountType, "Student") == 0) {
                    studentRole(storedStudentID);
                } else if (strcmp(storedAccountType, "Program Coordinator") == 0) {
                    programCoord(storedStudentID);
                } else if (strcmp(storedAccountType, "Program Leader") == 0) {
                    programLeader(storedStudentID);
                }
                return true;
            }
        }
        fclose(file);
    }

    return false;
}

void registration() {
    char username[20], password[20], accounttype[20], studentID[20];
    int choice;
    printf("Welcome to the registration page\n");
    printf("==============================\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    printf("Choose Type:\n");
    printf("1. Student\n");
    printf("2. Program Coordinator\n");
    printf("3. Program Leader\n");
    printf("Enter a number: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(accounttype, "Student");
            strcpy(studentID, generateRandomStudentID("S"));
            break;
        case 2:
            strcpy(accounttype, "Program Coordinator");
            strcpy(studentID, generateRandomStudentID("C"));
            break;
        case 3:
            strcpy(accounttype, "Program Leader");
            strcpy(studentID, generateRandomStudentID("L"));
            break;
        default:
            printf("Invalid Input. Please choose a number.\n");
            return;
    }

    FILE *loginFile, *StudentAccount;
    loginFile = fopen("Login.txt", "a");
    StudentAccount = fopen("StudentAccounts.txt", "a");
    fprintf(loginFile, "%s;%s;%s;%s\n", studentID, username, password, accounttype);
    if (strcmp(accounttype, "Student") == 0) {
        fprintf(StudentAccount, "%s,\n", studentID);
    }
    fclose(loginFile);
    fclose(StudentAccount);
    printf("Registration successful...\n");
    login();
}

void admin() {
    int choice;
    printf("Admin Menu\n");
    printf("1. REGISTRATION\n");
    printf("2. Manage Users\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registration();
            break;
        case 2:
            ManageUsers();
            break;
        case 3:
            exit(0);
        default:
            invalidChoice();
            break;
    }
}

void ManageUsers() {
    int choice;
    printf("Manage Users Menu\n");
    printf("1. Delete User\n");
    printf("2. Update User\n");
    printf("3. Back to Admin Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            deleteUser();
            break;
        case 2:
            updateUser();
            break;
        case 3:
            admin();
            break;
        default:
            invalidChoice();
            break;
    }
}

void deleteUser() {
    char username[20];
    printf("Enter the username to delete: ");
    scanf("%s", username);

    FILE *file = fopen("Login.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file != NULL && tempFile != NULL) {
        char storedUsername[20], storedPassword[20], storedAccountType[20], storedStudentID[20];

        while (fscanf(file, "%19[^;];%19[^;];%19[^;];%19[^\n]\n", 
                      storedStudentID, storedUsername, storedPassword, storedAccountType) == 4) {
            if (strcmp(username, storedUsername) != 0) {
                fprintf(tempFile, "%s;%s;%s;%s\n", storedStudentID, storedUsername, storedPassword, storedAccountType);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("Login.txt");
        rename("temp.txt", "Login.txt");

        printf("User deleted successfully.\n");
    } else {
        printf("Error opening files.\n");
    }
    login();
}

void updateUser() {
    char username[20];
    printf("Enter the username to update: ");
    scanf("%s", username);

    FILE *file = fopen("Login.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file != NULL && tempFile != NULL) {
        char storedUsername[20], storedPassword[20], storedAccountType[20], storedStudentID[20];

        while (fscanf(file, "%19[^;];%19[^;];%19[^;];%19[^\n]\n", 
                      storedStudentID, storedUsername, storedPassword, storedAccountType) == 4) {
            if (strcmp(username, storedUsername) == 0) {
                int updateChoice;
                printf("Select what you want to update:\n");
                printf("1. Username\n");
                printf("2. Password\n");
                printf("3. Both\n");
                printf("Enter your choice: ");
                scanf("%d", &updateChoice);

                char newUsername[20], newPassword[20];
                printf("Enter the new value: ");
                switch (updateChoice) {
                    case 1:
                        scanf("%s", newUsername);
                        strcpy(newPassword, storedPassword);
                        break;
                    case 2:
                        scanf("%s", newPassword);
                        strcpy(newUsername, storedUsername);
                        break;
                    case 3:
                        scanf("%s %s", newUsername, newPassword);
                        break;
                    default:
                        invalidChoice();
                        fclose(file);
                        fclose(tempFile);
                        remove("temp.txt");
                        return;
                }

                fprintf(tempFile, "%s;%s;%s;%s\n", storedStudentID, newUsername, newPassword, storedAccountType);
                printf("User updated successfully.\n");
            } else {
                fprintf(tempFile, "%s;%s;%s;%s\n", storedStudentID, storedUsername, storedPassword, storedAccountType);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("Login.txt");
        rename("temp.txt", "Login.txt");
    } else {
        printf("Error opening files.\n");
    }
}


void activityMenu(char *type)
{
    int choiceA;

    //display the neu and get the type

    printf("\n__Activity Menu__\n");
    printf("1. Talk\n");
    printf("2. Workshop\n");
    printf("3. Club\n");
    printf("4. Society\n");
    printf("5. Competition\n");
    printf("6. Exit\n");
    printf("Choice: ");
    // get the choice and clear input buffer
    scanf(" %d", &choiceA);
    while (getchar() != '\n');

    switch (choiceA)
    {
    case 1:
        strcpy(type, "Talk");
        break;
    case 2:
        strcpy(type, "Workshop");
        break;
    case 3:
        strcpy(type, "Club");
        break;
    case 4:
        strcpy(type, "Society");
        break;
    case 5:
        strcpy(type, "Competition");
        break;
    case 6:
        strcpy(type, "Exit");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

void typeMenu(char *type)
{
    int choice;

    printf("Enter the Type for the activity:\n");
    printf("1. Activity\n");
    printf("2. Core Module\n");
    printf("3. Elective Module\n");
    printf("4. Specialise Module\n");
    printf("5. Exit\n");
    printf("Choice: ");
    scanf(" %d", &choice);
    while (getchar() != '\n');

    switch (choice)
    {
    case 1:
        activityMenu(type);
        break;
    case 2:
        strcpy(type, "Core Module");
        break;
    case 3:
        strcpy(type, "Elective Module");
        break;
    case 4:
        strcpy(type, "Specialise Module");
        break;  
    case 5:
        printf("Exit\n");
        strcpy(type, "Exit");
        break;
    default:
        printf("Invalid choice.\n");
    }
}


int view_Action(char *filename, char *typeToView)
{
    FILE *activity;
    activity = fopen(filename, "r");

    if (activity == NULL)
    {
        perror("File open error");
        return 0;
    }

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), activity) != NULL)
    {
        char *token = strtok(line, ";");
        if (token != NULL)
        {
            char code[20];
            strncpy(code, token, sizeof(code));

            token = strtok(NULL, ";");
            if (token != NULL)
            {
                char name[70];
                strncpy(name, token, sizeof(name));

                token = strtok(NULL, ";");
                if (token != NULL)
                {
                    char type[20];
                    strncpy(type, token, sizeof(type));

                    token = strtok(NULL, ";");
                    if (token != NULL)
                    {
                        float points = atof(token);
                        if (strcmp(type, typeToView) == 0)
                        {
                            printf("Code: %s\tName: %s\tType: %s\tPoints: %.2f\n", code, name, type, points);
                            // Increment count for valid activity
                            count++; 
                        }
                        else if (strcmp(typeToView, "All") == 0)
                        {
                            printf("Code: %s\tName: %s\tType: %s\tPoints: %.2f\n", code, name, type, points);
                            count++;
                        }
                    }
                }
            }
        }
    }

    fclose(activity);

    return count;
}

// Function to view all activities
void view(struct Activity activities[], char *filename){
    int choice;
    char typeToView[20];


    //loop to not exit the menu until entering (6)
    do
    {
        // display the View menu
        printf("\n__View menu__\n");
        printf("1. View Activities\n");
        printf("2. View Core Modules\n");
        printf("3. View Elective Modules\n");
        printf("4. View Specialise Module\n");
        printf("5. View All\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        // get choice and Clear input buffer
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }


        switch (choice)
        {
        case 1:
        //display the Activity menue
        //get the typeToView from the function
            activityMenu(typeToView);
            printf("%s (Activities):\n", typeToView);
            view_Action(filename, typeToView);
            break;
        case 2:
            //set typeToView to core modules
            //display the core modules
            printf("Core Modules:\n");
            strcpy(typeToView, "Core Module");
            view_Action(filename, typeToView);
            break;
        case 3:
            //set typeToView to Elective Modules
            //display the Elective Modules
            printf("Elective Modules:\n");
            strcpy(typeToView, "Elective Module");
            view_Action(filename, typeToView);
            break;
        case 4:
            //set typeToView to Specialise Module
            //display the Specialise Module
            printf("Specialise Module:\n");
            strcpy(typeToView, "Specialise Module");
            view_Action(filename, typeToView);
            break;
        case 5:
            //set typeToView to ALL 
            //display all activities
            printf("All:\n");
            strcpy(typeToView, "All");
            view_Action(filename, typeToView);
            break;
        case 6:
            strcpy(typeToView, "");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 6);
}

// Function to delete a row from a text file based on a specified code
void deleteRowFromFile(const char *filename, const char *codeToDelete)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("File open error");
        return;
    }

    char tempFilename[] = "temp.txt";
    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL)
    {
        perror("Temp file open error");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, codeToDelete) == NULL)
        {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove(filename) != 0 || rename(tempFilename, filename) != 0)
    {
        perror("File operation error");
        return;
    }

    printf("Code %s has been deleted.\n", codeToDelete);
}

// Function to check if an activity already exists in the list
int isDuplicateActivity(const struct Activity activities[], int count, const char *code, const char *name)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(activities[i].code, code) == 0 || strcmp(activities[i].name, name) == 0)
        {
            // activity with the same code or name already exists
            return 1;
        }
    }
    // No duplicate found
    return 0; 
}

// Function to add the data
void addData(struct Activity **activities, int *count, const char *filename)
{
    char codeToAdd[20];
    char nameToAdd[70];
    char typeToAdd[20];
    float pointsToAdd;
    int choice;
    char prefix[5];
    //get the code to add and clear the input buffer
    printf("Enter the code to add: ");
    scanf("%s", codeToAdd);
    while (getchar() != '\n')
        continue;
        //check duplication
    if (isDuplicateActivity(*activities, *count, codeToAdd, ""))
    {
        printf("The code already exists. It will not be added.\n");
        return;
    }

    // get the name
    printf("Enter the name to add: ");
    scanf(" %[^\n]", nameToAdd);
    while (getchar() != '\n')
        continue;
    // check duplication
    if (isDuplicateActivity(*activities, *count, "", nameToAdd))
    {
        printf("The name already exists. It will not be added.\n");
        return;
    }

    typeMenu(typeToAdd);
    //if the return type = exit exit the function
    if (strcmp(typeToAdd, "Exit") == 0)
    {
        printf("Exit\n");
        return;
    }

    //assign the prefix code
    if(strcmp(typeToAdd,"Elective Module")== 0){
        strcpy(prefix,"E");
        strcat(prefix,codeToAdd);
    }

    if(strcmp(typeToAdd,"Talk")== 0){
        strcpy(prefix,"T");
        strcat(prefix,codeToAdd);
    }
    
    if(strcmp(typeToAdd,"Workshop")== 0){
        strcpy(prefix,"W");
        strcat(prefix,codeToAdd);

    }

    if(strcmp(typeToAdd,"Club")== 0){
        strcpy(prefix,"PC");
        strcat(prefix,codeToAdd);
    }

    if(strcmp(typeToAdd,"Society")== 0){
        strcpy(prefix,"CS");
        strcat(prefix,codeToAdd);
    }    
    if(strcmp(typeToAdd,"Competition")== 0){
        strcpy(prefix,"CT");
        strcat(prefix,codeToAdd);
    }
    
    if(strcmp(typeToAdd,"Specialise Module")== 0){
        strcpy(prefix,"SM");
        strcat(prefix,codeToAdd);
    }

    //the type = Core Module assign theprefix code and points to 30 
    if (strcmp(typeToAdd, "Core Module") == 0)
    {
        printf("The core Modules has 3 credits\n");
        pointsToAdd = 30;
        strcpy(prefix,"CM");
        strcat(prefix,codeToAdd);

    }
    else
    {
        printf("Enter the points: ");
        if (scanf("%f", &pointsToAdd) != 1)
        {
            printf("Invalid input. Please enter a number for points.\n");
            while (getchar() != '\n')
                continue;
            return;
        }
    }

    // Dynamically allocate memory for the new activity
    struct Activity *newActivity = realloc(*activities, (*count + 1) * sizeof(struct Activity));
    if (newActivity == NULL)
    {
        perror("Memory allocation error");
        return;
    }

    // Update activities pointer and count
    *activities = newActivity;
    int index = *count;

    // Copy data into the new activity
    snprintf((*activities)[index].code, sizeof((*activities)[index].code), "%s", prefix);
    snprintf((*activities)[index].name, sizeof((*activities)[index].name), "%s", nameToAdd);
    snprintf((*activities)[index].type, sizeof((*activities)[index].type), "%s", typeToAdd);
    (*activities)[index].points = pointsToAdd;

    // Update the count
    (*count)++;

    // Open the file for appending
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("File open error");
        return;
    }

    // Write the new activity to the file
    fprintf(file, "%s;%s;%s;%.2f\n", prefix, nameToAdd, typeToAdd, pointsToAdd);

    fclose(file);

    printf("Activity added to the file.\n");
}


// Function to delete an activity or core module
void deleteData(struct Activity activities[], int *count, const char *filename)
{
    int found = 0;

    char codeToDelete[20];
    printf("Enter the code of the activity to delete: ");
    scanf("%s", codeToDelete);
    // allocate the code line
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(activities[i].code, codeToDelete) == 0)
        {
            found = 1;
            for (int j = i; j < (*count - 1); j++)
            {
                activities[j] = activities[j + 1];
            }
            (*count)--;
            break;
        }
    }
    // delete the raw
    if (found)
    {
        deleteRowFromFile(filename, codeToDelete);
    }
    else
    {
        printf("Code %s not found.\n", codeToDelete);
    }
}

// Function to read activities or core modules from a text file
int readData(struct Activity **activities, const char *filename)
{
    //check if the file exist
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("File open error");
        return 0;
    }

    int count = 0;
    char line[150];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, ";");
        if (token != NULL)
        {
            if (count == 0)
            {
                *activities = malloc(sizeof(struct Activity));
            }
            else
            {
                *activities = realloc(*activities, (count + 1) * sizeof(struct Activity));
            }

            // Ensure null-termination of the code field
            strncpy((*activities)[count].code, token, sizeof((*activities)[count].code));

            token = strtok(NULL, ";");
            if (token != NULL)
            {
                strncpy((*activities)[count].name, token, sizeof((*activities)[count].name));

                token = strtok(NULL, ";");
                if (token != NULL)
                {
                    strncpy((*activities)[count].type, token, sizeof((*activities)[count].type));

                    token = strtok(NULL, ";");
                    if (token != NULL)
                    {
                        (*activities)[count].points = atof(token);

                        count++;
                    }
                }
            }
        }
    }

    fclose(file);
    return count;
}

// Function to update the data
void updateData(int count, const char *filename)
{
    struct Activity *activities = NULL;
    int found = 0;
    char codeToUpdate[20];
    char newName[70];
    char newtype[20];
    float newPoints;

    // Read data from the file to get rhe readCount
    int readCount = readData(&activities, filename);
    //file doesnt have any data ? output no data
    if (readCount == 0)
    {
        printf("No data found in the file.\n");
        return;
    }

    //get the code
    printf("Enter the code of the activity to update: ");
    scanf("%s", codeToUpdate);

    // Search for the code in the activities array
    for (int i = 0; i < readCount; i++)
    { 
        if (strcmp(activities[i].code, codeToUpdate) == 0)
        // show the data
        {
            found = 1;
            printf("Current details for activity %s:\n", codeToUpdate);
            printf("Name: %s\n", activities[i].name);
            printf("Type: %s\n", activities[i].type);
            printf("Points: %.2f\n", activities[i].points);
            break;
        }
    }
    
    //get the updated data
    if (found)
    {
        printf("Enter the new name for the activity: ");
        scanf(" %[^\n]", newName);

        typeMenu(newtype);
        if (strcmp(newtype, "Exit") != 0)
        {
            //check if type not Core Module to get the updated points
            if (strcmp(newtype, "Core Module") != 0)
        {
            printf("Enter the new points for the activity: ");
            //check if the input is an numaric or not
            if (scanf("%f", &newPoints) != 1)
            {
                printf("Invalid input. Please enter a number for points.\n");
                while (getchar() != '\n')
                    continue;
            }}
            //if the type is Core Module the points will be 30 
            else{
                newPoints = 30;
            }

            // Update the data in the array
            for (int i = 0; i < readCount; i++)
            {
                if (strcmp(activities[i].code, codeToUpdate) == 0)
                {
                    strncpy(activities[i].name, newName, sizeof(activities[i].name));
                    strncpy(activities[i].type, newtype, sizeof(activities[i].type));
                    activities[i].points = newPoints;
                    break;
                }
            }

            // Update the data in the file
            FILE *file = fopen(filename, "w");
            if (file == NULL)
            {
                perror("File open error");
                return;
            }

            for (int i = 0; i < readCount; i++)
            {
                fprintf(file, "%s;%s;%s;%.2f\n", activities[i].code, activities[i].name,
                        activities[i].type, activities[i].points);
            }

            fclose(file);
            printf("Code %s has been updated.\n", codeToUpdate);
        }
        else
        {
            printf("Exit\n");
        }
    }
    else
    {
        printf("Code %s not found.\n", codeToUpdate);
    }

    // Free dynamically allocated memory
    free(activities);
}

int programCoord(){

    // Initialize to NULL initially
    struct Activity *activities = NULL; 
    int activityCount = readData(&activities, "ActivityCoord.txt");
    int choice;

    do
    {
        printf("\nMenu:\n");
        printf("1. View activities and points\n");
        printf("2. Add an activity\n");
        printf("3. Delete an activity\n");
        printf("4. Update \n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        // get the choice and clear input buffer
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ; 
            continue;
        }

        switch (choice)
        {
        case 1:
            // Initialize to NULL initially
            view(activities, "ActivityCoord.txt"); // Call the function to display credits and points
            break;

        case 2:
            // Add an activity
            addData(&activities, &activityCount, "ActivityCoord.txt");
            break;

            
        case 3:
            // Delete an activity
            deleteData(activities, &activityCount, "ActivityCoord.txt");
            break;

        case 4:
            // update data
            updateData(activityCount, "ActivityCoord.txt");
            break;

        case 5:
            // Quit the Coordinator function
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    free(activities);
    return 0;
}

void programLeader() {
    printf("Program Leader Menu\n");
    // Implement the functionality for Program Leader
}

void invalidChoice() {
    printf("Invalid choice. Please try again.\n");
}

char* generateRandomStudentID(const char prefix[]) {
    static char studentID[20];
    sprintf(studentID, "%s%04d", prefix, rand() % 10000);
    return studentID;
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

#include <stdio.h>
#include <string.h>

void addActivity(const char *studentID, const char *codeToAdd) {
    FILE *file = fopen("StudentAccounts.txt", "r+");

    if (file == NULL) {
        perror("Error opening student file");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char studentRecord[256];
        strcpy(studentRecord, line);
        char *token = strtok(studentRecord, ",");
        
        if (token != NULL && strcmp(token, studentID) == 0) {
            found = 1;
            char *activities = strtok(NULL, "\n"); // Get the activities part

            if (activities != NULL) {
                // Check if the activity is already in the student's list
                char *activityToken = strtok(activities, ";");
                int activityFound = 0;

                while (activityToken != NULL) {
                    if (strcmp(activityToken, codeToAdd) == 0) {
                        activityFound = 1;
                        break;
                    }
                    activityToken = strtok(NULL, ";");
                }

                if (!activityFound) {
                    // Append the new activity code to the student's list
                    if (strlen(activities) + strlen(codeToAdd) + 1 < sizeof(line)) {
                        strcat(activities, ";");
                        strcat(activities, codeToAdd);
                        fseek(file, -strlen(line), SEEK_CUR);
                        fputs(line, file);
                        printf("Activity code %s added to student %s.\n", codeToAdd, studentID);
                    } else {
                        printf("Error: Activities list is too long.\n");
                    }
                } else {
                    printf("Activity code %s is already added to student %s.\n", codeToAdd, studentID);
                }
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("Student ID %s not found.\n", studentID);
    }
}


// Function to view any activity using the prefix code and their associated points
void ShowActivities(const char *codePrefix) {
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

        if (strncmp(code, codePrefix, strlen(codePrefix)) == 0) {
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
        printf("2. Select an Core Module\n");
        printf("3. Delete an Core Module\n");
        printf("4. Select Activity\n");
        printf("5. Delete an Activity\n");
        printf("6. Quit\n");
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
                ShowActivities("CM");
                printf("Enter the code of the activity to add: ");
                scanf("%s", codeToAdd);
                while (getchar() != '\n'); // Clear input buffer
                // Add the activity to the list of chosen activities and also write it to Activity.txt
                addActivity(ID,codeToAdd);
                break;
            case 3:
                printf("Enter the code of the activity to delete from your Activity.txt file: ");
                scanf("%s", codeToDelete);
                deleteActivity(ID, codeToDelete,"CM");
                break;
            case 4:
                ShowActivities("E");
                ShowActivities("SM");
                ShowActivities("W");
                ShowActivities("CS");
                ShowActivities("PS");
                ShowActivities("PC");
                ShowActivities("CMP");
                ShowActivities("T");

                break;
            case 5:
                printf("Enter the code of the core module to delete: ");
                scanf("%s", codeToDelete);
                //deleteData(activities, &count, "coreModules.txt", codeToDelete,"CM");
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}