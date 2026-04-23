#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct tutor{
    char tid[20];
    char name[20];
    char title[1000];
    char tcode[20];
    char tpass[30];
};

struct session{
    char sid[100];
    char stitle[1000];
    char sday[100];
    char stime[100];
    char slocation[100];
    char tid[100];
};

struct student{
    char tpno[30];
    char name[20];
    char spass[30]; 
}; 

void displayMenuAdmin();
int SignIn(char* username, char* password, int ch);
void RegisterTutor(); 
void AddSession(); 
void SearchTutor(); 
void viewTutorList(); 
void viewStudentList(); 
void viewSessionList(); 
void DisplayList(); 
void displayStudentInfo();
void sessionlistTutor(); 
void sessionlistStudent();

int SignIn(char* username, char* password, int ch) {
    FILE* fp, * fpa, * fpt, * fps;
    char user[100], pass[100];
    int sign, i = 3; 
    
    fp=fopen("accountadmin.txt","w");
    fprintf(fp,"admin | 000");
    fclose(fp);

    do {
        printf("\n|\t SignIN \t|\n\n");

        printf("\n Username: ");
        scanf("%s", username);
        printf("\n Password: ");
        scanf("%s", password);

        sign = 0; 

        if (ch == 1) {
            fpa = fopen("accountadmin.txt", "r");

            while (fscanf(fpa, "%s | %s\n", user, pass) != EOF) {
                if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
                    printf("\nSign In Successful\n");
                    sign = 1;
                    i=-2;
                }
            }
            fclose(fpa);

            if (!sign) {
                printf("\nFailed to Sign In \n%d attempt(s) remaining\n", i);
                i = i - 1;
            }
        }
        else if (ch == 2) {
            fpt = fopen("accounttutor.txt", "r");

            while (fscanf(fpt, "%s | %s\n", user, pass) != EOF) {
                if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
                    printf("\nSign In Successful\n");
                    sign = 1;
                    i=-2;
                }
            }
            fclose(fpt);

            if (!sign) {
                printf("\nFailed to Sign In \n%d attempt(s) remaining\n", i);
                i = i - 1;
            }
        }
        else if (ch == 3) {
            fps = fopen("accountstudent.txt", "r");

            while (fscanf(fps, "%s | %s\n", user, pass) != EOF) {
                if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
                    printf("\nSign In Successful\n");
                    sign = 1;
                    i=-2;
                }
            }
            fclose(fps);

            if (!sign) {
                printf("\nFailed to Sign In \n%d attempt(s) remaining\n", i);
                i = i - 1;
            }
        }
    } 
    while (i > -1);

    if (i== -1) {
        ch= 0;
    }
    
    return ch;
}




//Admin user type 

void displayMenuAdmin() {
    printf("\n1- Registeration of Tutor\n");
    printf("2- Add new programming cafe session\n");
    printf("3- Registration of Student\n");
    printf("4- Enroll Student in Session\n");
    printf("5- List of Programming Cafe sessions and Participating Students \n"); 
    printf("6- Exit \n");
    printf("---------------------------------\n"); 
} 

void RegisterTutor(){
    FILE*fp, *fpt;
    struct tutor tinfo;
    char ch;
    do{
        printf("\n|\t Add Tutor \t|\n\n");
        fp=fopen("tutorinfo.txt","a");
        fpt=fopen("accounttutor.txt","a"); 
        
        printf("Enter Tutor ID= ");
        scanf("%s",tinfo.tid);
        fprintf(fp,"Tutor ID: %s\n",tinfo.tid); 
        
        printf("Enter Tutor Name= ");
        scanf("%s",tinfo.name);
        fprintf(fp,"Tutor Name: %s\n",tinfo.name);
        
        printf("Enter Program Title (No spaces)= ");
        scanf(" %s", tinfo.title);
        fprintf(fp,"Tutor Title: %s\n",tinfo.title);
        
        printf("Enter Tutor Code= ");
        scanf("%s",tinfo.tcode);
        fprintf(fp,"Tutor Code: %s\n",tinfo.tcode); 
        
        printf("Enter Tutor Password= ");
        scanf("%s",tinfo.tpass); 
        fprintf(fp,"Tutor Password: %s\n",tinfo.tpass);
        
        fprintf(fp,"\n-------------------\n");
        
        fprintf(fpt,"%s | %s\n", tinfo.tid, tinfo.tpass);
        
        if(fp==NULL || fpt==NULL){
            printf("\n Cannot Open File\n");
        }
        else{
            printf("\n Record Stored Sucessfully\n");
        }
        
        fclose(fp); 
        fclose(fpt);
        
    
        printf("\n Do you want to add another Tutor record (Y/N)= ");
        scanf("%s",&ch);
    }
    while(ch=='Y'||ch=='y'); 
} 

void AddSession(){
    FILE*fp; 
    struct session adds;
    char ch;
    do{
        printf("\n|\t Add Session \t|\n\n");
        fp=fopen("session.txt","a"); 
        
        printf("Enter Session Code= ");
        scanf("%s",adds.sid);
        fprintf(fp,"Session Code: %s\n",adds.sid);
        
        printf("Enter Language Title (No spaces)= ");
        scanf("%s", adds.stitle); 
        fprintf(fp,"Language title (Study Field): %s\n",adds.stitle);
        
        printf("Enter Session Day= ");
        scanf("%s",adds.sday); 
        fprintf(fp,"Session Day: %s\n",adds.sday); 
        
        printf("Enter Session Time= ");
        scanf("%s",adds.stime); 
        fprintf(fp,"Session Time: %s\n",adds.stime); 
        
        printf("Enter Session Location= ");
        scanf("%s",adds.slocation); 
        fprintf(fp,"Session Loction: %s\n",adds.slocation);  
        
        printf("Enter Tutor Code= "); 
        scanf("%s",adds.tid); 
        fprintf(fp,"Tutor Code: %s\n",adds.tid); 
        
        fprintf(fp,"\n-------------------\n");
        
        if(fp==NULL){
            printf("\n Cannot Open File"); 
        }
        else{
            printf("\n Record Stored Successfully \n");
        } 
        
        fclose(fp);
        
        printf("\n Do you want to add another Session (Y/N)= ");
        scanf("%s",&ch);
    }
    while(ch=='Y'||ch=='y'); 
}


void RegisterStudent(){ 
    FILE*fp, *fps;
    struct student sinfo;
    char ch; 
    
    do{
        printf("\n|\t Add Student \t|\n\n");
        fp=fopen("studentinfo.txt","a");
        fps=fopen("accountstudent.txt","a"); 
        
        printf("Enter Student Name= "); 
        scanf("%s",sinfo.name);
        fprintf(fp,"Student name: %s\n",sinfo.name); 
        
        printf("Enter TpNumber(TPXXXXXX)= ");
        scanf("%s",sinfo.tpno);
        fprintf(fp,"TP Number: %s\n",sinfo.tpno); 
        
        printf("Enter Password= ");
        scanf("%s",sinfo.spass);
        fprintf(fp,"Password: %s\n",sinfo.spass);
        
        fprintf(fp,"\n-------------------\n");
        
        fprintf(fps,"%s | %s\n", sinfo.tpno, sinfo.spass);
        
        if(fp==NULL || fps==NULL){
            printf("\n Cannot Open File");
        }
        else{
            printf("\n Record Stored Sucessfully"); 
        }
        
        fclose(fp);
        fclose(fps);
        
        printf("\n Do you want to add another Student record (Y/N)= "); 
        scanf("%s",&ch);
    }
    while(ch=='Y'||ch=='y'); 
    
}

void EnrollStudent() {
    FILE *sessionFile, *studentFile, *enrollmentFile;
    struct session sessionInfo;
    struct student studentInfo;
    char sessionCode[100], tpNumber[100]; 
    
    printf("\n|\t Enroll Student in Session \t|\n\n");

    sessionFile = fopen("session.txt", "r");
    if (sessionFile == NULL) {
        printf("Cannot open session file.\n");
        return;
    }

    printf("Enter Session Code: ");
    scanf("%s", sessionCode);

    int sessionFound = 0;
    while (fscanf(sessionFile, "Session Code: %s\nLanguage title (Study Field): %s\nSession Day: %s\nSession Time: %s\nSession Loction: %s\nTutor Code: %s\n-------------------\n",
                sessionInfo.sid, sessionInfo.stitle, sessionInfo.sday, sessionInfo.stime, sessionInfo.slocation, sessionInfo.tid) != EOF) {
                    if (strcmp(sessionInfo.sid, sessionCode) == 0) {
                        sessionFound = 1;
                        printf("Session found!\n");
                        break;
                    }
                }
                fclose(sessionFile);

    if (!sessionFound) {
        printf("Session not found.\n");
        return;
    } 

    studentFile = fopen("studentinfo.txt", "r");
    if (studentFile == NULL) {
        printf("Cannot open student info file.\n");
        return;
    }

    printf("Enter Student TP Number: ");
    scanf("%s", tpNumber);

    int studentFound = 0;
    while (fscanf(studentFile, "Student name: %s\nTP Number: %s\nPassword: %s\n-------------------\n",
                studentInfo.name, studentInfo.tpno, studentInfo.spass) != EOF) {
        if (strcmp(studentInfo.tpno, tpNumber) == 0) {
            studentFound = 1;
            printf("Student found!\n");
            break; 
        }
    }

    fclose(studentFile);

    if (!studentFound) {
        printf("Student not found.\n");
        return;
    } 

    enrollmentFile = fopen("studentnsessionlist.txt", "a");
    if (enrollmentFile == NULL) {
        printf("Cannot create enrollment file.\n");
        return;
    } 
    
    fprintf(enrollmentFile, "Student name: %s\n", studentInfo.name);
    fprintf(enrollmentFile, "TP Number: %s\n", studentInfo.tpno);
    fprintf(enrollmentFile, "Enrolled Session Code: %s\n", sessionInfo.sid);
    fprintf(enrollmentFile, "Language title (Study Field): %s\n", sessionInfo.stitle);
    fprintf(enrollmentFile, "Session Day: %s\n", sessionInfo.sday);
    fprintf(enrollmentFile, "Session Time: %s\n", sessionInfo.stime);
    fprintf(enrollmentFile, "Session Location: %s\n", sessionInfo.slocation);
    fprintf(enrollmentFile, "Tutor Code: %s\n", sessionInfo.tid);
    fprintf(enrollmentFile,"\n-------------------\n");

    printf("\nStudent enrolled in the session successfully!\n"); 
    
    fclose(enrollmentFile);
} 

void DisplayList() {
    FILE *fp = fopen("studentnsessionlist.txt", "r");

    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }

    char studentName[100], sessionCode[100], tutorCode[100], sessionLocation[100]; 
    
    printf("---------------------- All Session List ----------------------\n");
    printf("|| Student Name || Session Code || Tutor Code || Location ||\n");
    printf("---------------------------------------------------------------\n");

    while (fscanf(fp, "Student name: %s\nTP Number: %*s\nEnrolled Session Code: %s\nLanguage title (Study Field): %*s\nSession Day: %*s\nSession Time: %*s\nSession Location: %s\nTutor Code: %s\n-------------------\n",
                studentName, sessionCode, sessionLocation, tutorCode) != EOF) {
                    printf("| %s | %s | %s | %s |\n", studentName, sessionCode, tutorCode, sessionLocation);
                    printf("---------------------------------------------------------------\n"); 
                }
                fclose(fp);
} 

/*void viewTutorList() {
  FILE *fp = fopen("tutorinfo.txt", "r");

  if (fp == NULL) {
    printf("File does not exist.\n");
    return;
  }
  
  char data[1000][1000];
  int i,line=0;
  
  while(!feof(fp) && !ferror(fp)){
      
      if(fgets(data[line],1000,fp) !=NULL){
          line++;
      }
  }
  fclose(fp); 
  
  for(i=0;i<line;i++){
      printf("%s",data[i]);
  }
} */


//Tutor user type 
void displaymenututor(){
    printf("\n1- View Session List \n"); 
    printf("2- Exit \n");
    printf("---------------------------------\n"); 
} 


void sessionlistTutor() {
    char tcode[100]; 

    printf("Enter Tutor Code: ");
    scanf("%s", tcode);

    FILE* fp;
    struct session sinfo;
    fp = fopen("session.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    int found = 0; 
    
     printf("\n|\t Tutor Session List \t|\n\n");
    printf("|| Code || Title || Day || Time || Location ||\n");
    printf("---------------------------------------------------------------\n"); 

    while (fscanf(fp, "Session Code: %s\nLanguage title (Study Field): %s\nSession Day: %s\nSession Time: %s\nSession Loction: %s\nTutor Code: %s\n-------------------\n",
        sinfo.sid, sinfo.stitle, sinfo.sday, sinfo.stime, sinfo.slocation, sinfo.tid) != EOF) {
        if (strcmp(sinfo.tid, tcode) == 0) {
            printf("| %s | %s | %s | %s | %s |\n",sinfo.sid,sinfo.stitle,sinfo.sday,sinfo.stime,sinfo.slocation); 
            printf("---------------------------------------------------------------\n");
            found = 1; 
        }
    }

    fclose(fp);

    if (!found) {
        printf("No matching sessions found.\n");
    }
}



//Student user type
void displaymenustudent(){
    printf("\n1- View your Session list \n"); 
    printf("2- Enroll in available sessions \n");  
    printf("3- Exit \n");
    printf("---------------------------------\n"); 
} 

void sessionlistStudent() {
    char tpno[100]; 

    printf("Enter Tpnumber: ");
    scanf("%s", tpno);

    FILE* fp;
    fp = fopen("studentnsessionlist.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    int found = 0; 
    char tpnumber[100], sessionCode[100], sessionTitle[100], sessionDay[100], sessionTime[100], sessionLocation[100];
    
    printf("\n|\t Student Session List \t|\n\n");
    printf("|| Code || Title || Day || Time || Location ||\n");
    printf("---------------------------------------------------------------\n");

    while (fscanf(fp, "Student name: %*s\nTP Number: %s\nEnrolled Session Code: %s\nLanguage title (Study Field): %s\nSession Day: %s\nSession Time: %s\nSession Location: %s\nTutor Code: %*s\n-------------------\n", 
    tpnumber, sessionCode, sessionTitle, sessionDay, sessionTime, sessionLocation) != EOF) {
        if (strcmp(tpnumber, tpno) == 0) {
            printf("| %s | %s | %s | %s | %s |\n",sessionCode,sessionTitle,sessionDay,sessionTime,sessionLocation); 
            printf("---------------------------------------------------------------\n");
            found = 1; 
        }
    }

    fclose(fp);

    if (!found) {
        printf("No matching sessions found.\n");
    }
} 



//Extra 

void viewStudentList() {
    FILE *fp = fopen("studentinfo.txt", "r");

    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }

    char studentName[100], tpNumber[100]; 
    
    printf("\n|\t All Student List \t|\n\n");
    printf("|| Student Name || TP Number ||\n");
    printf("---------------------------------------------------------------\n");

    while (fscanf(fp, "Student name: %s\nTP Number: %s\nPassword: %*s\n-------------------\n",
                studentName, tpNumber) != EOF) {
        printf("| %s | %s |\n", studentName, tpNumber);
            printf("---------------------------------------------------------------\n"); 
    }

    fclose(fp);
} 

void viewSessionList() {
    FILE *fp = fopen("session.txt", "r");
    struct session sinfo; 

    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }

    char studentName[100], tpNumber[100]; 
    
    printf("\n|\t Available Session List \t|\n\n");
    printf("|| Session Code || Study Field || Day || Time || Location ||\n");
    printf("---------------------------------------------------------------\n");

    while (fscanf(fp, "Session Code: %s\nLanguage title (Study Field): %s\nSession Day: %s\nSession Time: %s\nSession Loction: %s\nTutor Code: %*s\n-------------------\n",
                sinfo.sid, sinfo.stitle, sinfo.sday, sinfo.stime, sinfo.slocation) != EOF) {
                    printf("| %s | %s | %s | %s | %s |\n", sinfo.sid, sinfo.stitle, sinfo.sday, sinfo.stime, sinfo.slocation);
                    printf("---------------------------------------------------------------\n"); 
                }
                
                fclose(fp);
} 


/*void displayStudentInfo(const char tpno) {
  FILE* fp;
  struct student sinfo;

  fp = fopen("studentinfo.txt", "r");
  if (fp == NULL) {
    printf("Cannot open file.\n");
    return;
  }

  while (fscanf(fp, "Student name: %s\nTP Number: %s\nPassword: %s\n-------------------\n",
                 sinfo.name, sinfo.tpno, sinfo.spass) != EOF) {
    if (strcmp(sinfo.tpno, tpno) == 0) {
      printf("Student TP: %s\n", sinfo.tpno);
      printf("Student Name: %s\n", sinfo.name);
      fclose(fp);
      return;
    }
  }

  fclose(fp);
  printf("Student not found.\n");
} */

// Main Function Man 

int main() {
    int ch;
    int choice;
    char username[100], password[100], tid[10]; 
    char tpno[50]; 
    
    printf("\n|\t Select User type \t|"); 
    printf("\n---------------------------------");
    printf("\n 1- Admin ");
    printf("\n 2- Tutor ");
    printf("\n 3- Student ");
    printf("\n Select User type= "); 
    scanf("%d",&ch); 
    
    if (ch < 1 || ch > 3) {
    printf("Invalid input. Please enter a valid user type.\n"); 
    return(0);
    } 
    
    ch=SignIn(username, password, ch); 
    
    if(ch==0){
        printf("\nFailed to Log In \n\n|WARNING MESSAGE SENT TO ADMIN !!!|");
        return(0);
    }
    else if(ch==1){ 
        printf("\n|\t Welcome Admin %s \t|\n", username);
        printf("\n---------------------------------\n"); 
        
        do {
        displayMenuAdmin();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Option 1 selected.\n\n");
                RegisterTutor();
                break;
            case 2:
                printf("Option 2 selected.\n\n");
                AddSession();
                break;
            case 3:
                printf("Option 3 selected.\n\n"); 
                RegisterStudent();
                break;
            case 4:
                printf("Option 4 selected.\n\n"); 
                viewSessionList(); 
                viewStudentList(); 
                EnrollStudent(); 
                break; 
            case 5:
                printf("Option 5 selected.\n\n");
                DisplayList();
                break;
            case 6:
                printf("Option 5 selected.\n\n");
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\n");
            
        } 
        while (choice != 6);
    } 
    else if(ch==2){ 
        printf("\n|\t Welcome Tutor %s \t|\n", username);
        printf("\n---------------------------------\n"); 
        
        do {
        displaymenututor();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Option 1 selected.\n\n");
                sessionlistTutor();
                break; 
            case 2:
                printf("Option 2 selected.\n\n");
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\n");
            
        } 
    while (choice != 2);
        
    } 
    else if(ch==3){ 
        printf("\n|\t Welcome Student %s \t|\n", username);
        printf("\n---------------------------------\n"); 
        
        do {
        displaymenustudent();
        printf("Enter your choice: ");
        scanf("%d", &choice); 

        switch (choice) {
            case 1:
                printf("Option 1 selected.\n\n");
                sessionlistStudent();
                break;
            case 2:
                printf("Option 2 selected.\n\n"); 
                viewSessionList();
                EnrollStudent();
                break;
            case 3:
                printf("Option 3 selected.\n\n"); 
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\n");
            
        } 
    while (choice != 3);
    }
    else{
        printf("Invalid number entered\n");
    }
   
    return 0;
}
