#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <windows.h>

#define MAX_STUDENTS 1000
#define MAX_ACTIVITY 100

void student_activity_add(FILE * activities, FILE * student);
void student_activity_update(FILE * student);
FILE * del(FILE * student);
void Student_Info_Display(FILE * student);
void update_password(FILE * tp);
void printChar(char ch, int n);
void title();

void gotoxy(int x, int y) {
    COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CRD);
}

struct activity {
    char code[5];
    char name[30];
    char type[20];
    int points;
} a;

struct Student {
    char name[30];
    int TPnumber;
    char participationType[30];
    int totalPoints;
    struct activity act[MAX_ACTIVITY];
} s;


/*---------------------------------------------*/

void ListFiles(const char* dirname){
    DIR *directory = opendir(dirname);

    if (directory==NULL)
    {
        printf("ERROR OPENING DIRECTORY.\n");
        return 1;
    }
    printf("reading files in: %s\n", dirname);

    struct dirent * entity;
    while ((entity = readdir(directory)) != NULL)
    {
        printf("%hdd %s/%s\n", entity->d_type, dirname, entity->d_name);
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, "..")!= 0)
        {
            char path[100] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            ListFiles(path);
        }
    }

    if (closedir(directory) == -1)
    {
        printf("ERROR CLOSING DIRECTORY.\n");
        return 1;
    }
}

void ReadDirectory(DIR *directory){

}

/*--------------------------------------------------------*/

int main(){
    char namingdir[20];
    printf("name the directory: \n");
    scanf("%s", namingdir);
    ListFiles(namingdir);
    
    FILE * activities;
    FILE * student;
    FILE * tp;
    
    if((activities=fopen("activities.txt","r+"))==NULL)
    {
        if((activities=fopen("activities.txt","r+"))==NULL)
        {
            printf("Can't create or open Database.");
            return 0;
        }
    }
    
    if (activities == NULL) {
        printf("Error opening user data file.\n");
        return 1;
    }

    if(ferror(activities)) {    
        printf("Error in reading from file!");
    }
    clearerr(activities);      
    if(ferror(activities)){   
        printf("Error again in reading from file!");
    }

    if((student=fopen("student.txt","r+"))==NULL)
    {
        if((student=fopen("student.txt","r+"))==NULL)
        {
            printf("Can't create or open Database.");
            return 0;
        }
    }
    
    if (student == NULL) {
        printf("Error opening user data file.\n");
        return 1;
    }

    if(ferror(student)) {    
        printf("Error in reading from file!");
    }
    clearerr(student);      
    if(ferror(student)){   
        printf("Error again in reading from file!");
    }
    /*----------------------------------------------*/

    int k,i;
    char pas[50];
    int option;
    SetConsoleTitle("Student Semester Planner | APU");

    while(1)
    {
        title();
        printf("\n\t");
        printChar('*',64);

        printf("\n\n\t\t\t\t1. Register To Activity");
        printf("\n\n\t\t\t\t2. Modify An Activity");
        printf("\n\n\t\t\t\t3. Unregister To Activity");
        printf("\n\n\t\t\t\t4. Show All Activities");
        printf("\n\n\t\t\t\t5. Change Password");
        printf("\n\n\t\t\t\t6. Logout\n\t");
        printChar('*',64);
        printf("\n\n\t\t\t\tEnter Your Option :--> ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                student_activity_add(activities, student);
                break;
            case 2:
                student_activity_update(student);
                break;
            case 3:
                student = del(student);
                break;
            case 4:
                Student_Info_Display(student);
                break;
            case 5:
                system("cls");
				system("color 5f");
                update_password(tp);
                break;
            case 6:
                return 1;
                break;
            default:
                printf("\n\t\tNo Action Detected");
                printf("\n\t\tPress Any Key\n\n\n");
                getch();
                system("pause");
        }
    }
    return 1;
}

/*--------------------------------------------------------*/

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

/*--------------------------------------------------------*/

void title()
{
    // system("cls");    
    system("COLOR 03");
    printf("\n\n\t");
    printChar('=',19);
    printf(" Student Semester Planner ");
    printChar('=',19);
    printf("\n\n");
}

/*--------------------------------------------------------*/

void update_password(FILE * tp)
{
    char c, pass[10];
    printf("\nEnter new password :");
    fflush(stdin);
    fgets(pass, 10, stdin);
    pass[strcspn(pass, "\n")] = 0; 

    printf("\nSave password (y/n) :");
    fflush(stdin);
    scanf("%c", &c);

    if(c == 'y' || c == 'Y')
    {
        tp = fopen("Password.txt", "w+");
        if (tp != NULL)
        {
            fwrite(pass, sizeof(char), strlen(pass), tp);
            fclose(tp);
            printf("\n\tPassword Saved\n");
        }
        else
        {
            printf("Failed to open the password file for writing.\n");
        }
    }
    else
    {
        printf("Password not saved :\n");
        printf("Press any key to continue >>>");
        getch();
    }
}

/*--------------------------------------------------------*/

void student_activity_add(FILE *activities, FILE *student) {
    char tempCode[5], line[100], studentLine[200];
    struct Student tempStudent;
    int tempTP, foundStudent = 0, actIndex = 0;

    printf("\n\n\tEnter TP number of Student: ");
    scanf("%d", &tempTP);

    rewind(student);
    while (fgets(studentLine, sizeof(studentLine), student) != NULL) {
        sscanf(studentLine, "%[^,],%d,%[^,],%d", tempStudent.name, &tempStudent.TPnumber, 
               tempStudent.participationType, &tempStudent.totalPoints);
        if (tempStudent.TPnumber == tempTP) {
            foundStudent = 1;
            break;
        }
    }

    if (foundStudent==0) {
        printf("\n\n\t!!!! ERROR !!!! STUDENT NOT FOUND\n");
        return;
    }

    if(foundStudent==1)
    {
        for (actIndex = 0; actIndex < MAX_ACTIVITY; actIndex++) {
            if (strlen(tempStudent.act[actIndex].name) == 0) break;
        }

        if (actIndex == MAX_ACTIVITY) {
            printf("\n\n\t!!!! ERROR !!!! ACTIVITY LIMIT REACHED\n");
            return;
        }

        printf("\n\n\t\tEnter Activity Code (e.g., A001): ");
        fflush(stdin);
        fgets(tempCode, sizeof(tempCode), stdin);
        tempCode[strcspn(tempCode, "\n")] = 0;

        rewind(activities);
        while (fgets(line, sizeof(line), activities) != NULL) {
            sscanf(line, "%[^;];%[^;];%[^;];%d", a.code, a.name, a.type, &a.points);

            if (strcmp(a.code, tempCode) == 0) {
                tempStudent.act[actIndex] = a;
                tempStudent.totalPoints += a.points;
                printf("\n\tActivity '%s' added to student record with %d points\n", a.name, a.points);
                break;
            }
        }

        if (strlen(a.name) == 0) {
            printf("\n\n\t!!!! ERROR !!!! ACTIVITY NOT FOUND\n");
            return;
        }

        fseek(student, -sizeof(struct Student), SEEK_CUR);
        fwrite(&tempStudent, sizeof(struct Student), 1, student);
    }
}

/*--------------------------------------------------------*/

void student_activity_update(FILE * student) {
    title();

    FILE * temp;
    int tempTP, flag = 0;
    struct Student tempStudent;

    printf("\n\n\tEnter TP Number of Student to modify the Record: ");
    scanf("%d", &tempTP);

    struct Student students[MAX_STUDENTS]; 
    int num_students = 0;

    rewind(student); 
    while (fread(&tempStudent, sizeof(struct Student), 1, student) == 1) {
        students[num_students] = tempStudent;
        if (tempStudent.TPnumber == tempTP) {
            flag = 1;
            break;
        }

    if (flag==1) {
        fseek(student, -sizeof(struct Student), SEEK_CUR);
        printf("\n\n\t\t\t\tRecord Found\n\t\t\t");
        printChar('=', 38);
        printf("\n\n\t\t\tStudent Name: %s", tempStudent.name);
        printf("\n\n\t\t\tStudent TP Number: %d\n\t\t\t", tempStudent.TPnumber);
        printChar('=', 38);
        printf("\n\n\t\t\tEnter New activity for the Student");
        
        printf("\n\n\t\t\tEnter Name of Activity: ");
        fflush(stdin);
        fgets(tempStudent.name, 30, stdin);
        tempStudent.name[strlen(tempStudent.name) - 1] = '\0';

        printf("\n\n\t\t\tEnter : ");
        fflush(stdin);
        fgets(tempStudent.participationType, 30, stdin);
        tempStudent.participationType[strlen(tempStudent.participationType) - 1] = '\0';

        printf("\n\n\t\t\tEnter TP number: ");
        scanf("%d", &tempStudent.TPnumber);

        students[num_students] = tempStudent;
        //}
        num_students++;
        fwrite(&tempStudent, sizeof(struct Student), 1, student);
        printf("\n\n\tRecord Updated Successfully");
    } else {
        printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");
    }

    printf("\n\n\t");
    system("pause");
    }
}

/*--------------------------------------------------------*/

FILE * del(FILE * student) {
    title();

    int flag = 0, tempTP;
    struct Student tempStudent;
    FILE *ft;

    if((ft = fopen("temp.txt", "w+")) == NULL) {
        printf("\n\n\t\t\t!!! ERROR !!!\n\t\t");
        system("pause");
        return student;
    }

    printf("\n\n\tEnter TP number of Student to Delete the Activity");
    printf("\n\n\t\t\tTP No. : ");
    scanf("%d", &tempTP);

    rewind(student);

    while(fread(&tempStudent, sizeof(struct Student), 1, student) == 1) {
        if(tempStudent.TPnumber == tempTP) {
            flag = 1;
            tempStudent.totalPoints -= tempStudent.act[MAX_ACTIVITY].points;
            memset(&tempStudent.act[MAX_ACTIVITY], 0, sizeof(struct activity)); 
        }
        fwrite(&tempStudent, sizeof(struct Student), 1, ft);
    }

    fclose(student);
    fclose(ft);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if(flag == 0) {
        printf("\n\n\t\tNO STUDENT FOUND WITH THE TP NUMBER %d\n\t", tempTP);
    }

    printChar('-', 65);
    printf("\n\t");
    system("pause");
    return student;
}

/*--------------------------------------------------------*/

void Student_Info_Display(FILE * student) {
    title();
    int tempTP, foundStudent = 0, siz = sizeof(struct Student);
    char tempCode[5], line[100], studentLine[200];
    struct Student tempStudent;

    rewind(student);

    printf("\n\n\tEnter TP number of Student to Display");
    printf("\n\n\t\t\tTP No. : ");
    scanf("%d", &tempTP);

    while (fgets(studentLine, sizeof(studentLine), student) != NULL) {
        sscanf(studentLine, "%[^,],%d,%[^,],%d", tempStudent.name, &tempStudent.TPnumber, 
               tempStudent.participationType, &tempStudent.totalPoints);
        if (tempStudent.TPnumber == tempTP) {
            foundStudent = 1;
            break;
        }
    }

    if (foundStudent==1)
    {
        while(fread(&s, siz, 1, student) == 0) {
            if(s.TPnumber == tempTP) {
                printf("\n\n\t\tTP number : %d", s.TPnumber);
                printf("\n\t\tName : %s", s.name);
                printf("\n\t\tActivity Name: %s", s.act[MAX_ACTIVITY].name);
                printf("\n\t\tActivity Type: %s", s.act[MAX_ACTIVITY].type);
                printf("\n\t\tActivity Points: %d", s.act[MAX_ACTIVITY].points);
                printf("\n\t\tTotal Points: %d", s.totalPoints);
                printChar('-', 65);
                break;
            }
        }
    }

    if (feof(student)) {
        printf("\n\n\tNo Student found with TP number %d", tempTP);
    }

    printf("\n\n\n\t");
    printChar('*', 65);
    printf("\n\n\t");
    system("pause");
}
