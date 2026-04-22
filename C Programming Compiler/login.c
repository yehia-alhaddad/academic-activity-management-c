#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ID_LENGTH
#define MAX_PWD_LENGTH


void login(fp, char, char);


typedef struct {
    char id[20];
    char pwd[10];
    char role[10];
}user;


int main()
{    
    // char names[3][30];
    // int marks[3][2][2];//std,sub,assesment
    // for(int std=0;std<3;std++){ //row
    //     printf("Enter Student Name:");
    //     scanf("%[^\n]*s",names[std]);
    //     //fgets(names[std],30,stdin);
    //     for(int sub=0;sub<2;sub++) { //col
    //         printf("student %s: Subject = %d\n", names[std],sub+1);
    //         for(int ass=0;ass<2;ass++){ //depth (z)
    //             printf("Assessment %d:",ass+1);
    //             scanf("%d", &marks[std][sub][ass]); 
    //         }
    //     }
    // }

    // for(int std=0;std<3;std++){ //row
    //     for(int sub=0;sub<2;sub++) { //col
    //         printf("student %d: Subject = %d\n", std+1,sub+1);
    //         for(int ass=0;ass<2;ass++){ //depth (z)
    //             printf("Assessment %d: %d\n",ass+1,marks[std][sub][ass]); 
    //         }
    //     }
    //     printf("\n");
    // }
    FILE *fp;
    fp = fopen("userdata.bin","rb+");
    if (fp == NULL) {
        printf("Error opening user data file.\n");
        return 1;
    }

    if(ferror(fp)) {    
        printf("Error in reading from file!");
    }
    clearerr(fp);      
    if(ferror(fp)){   
        printf("Error again in reading from file!");
    }

    /*----------------------------*/
    char array[15][15][15], line[200];
    char id, pwd;
    fgets(line, sizeof(line), fp);
    int row = atoi(line);
    int i;
    for(i = 0;i<row;++i){
        int col = 0;
        char *p;
        fgets(line, sizeof(line), fp);
        for(p = strtok(line, " \t\n");p;p=strtok(NULL, " \t\n")){
            strcpy(array[i][col++], p);
        }
        array[i][col][0] = '\0';
    }
    fclose(fp);
    {
        for(int i=0;i<row;++i){
            for(int j=0;array[i][j][0];++j)
                printf("%s ", array[i][j]);
            printf("\n");
        }
    }

    /*----------------------------*/
    int wordCount = 0, i, option;
    
    struct user;
    do
    {
        printf("1: login\n");
        printf("2: exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        int valid = 0;

        printf ( "Enter Student id: " );
        fgets(id, sizeof(id), stdin);
        printf("\n Enter your password: ");
        fgets(pwd, sizeof(pwd), stdin);
        login(fp, id, pwd);
    }while (option!=2);

    /*--------------------------------------------------------*/
}


void login(fp, id, pwd)
{
    fp = fopen("userdata.bin", "rb+");
    if((fp=fopen("userdata.txt","rb+"))==NULL)
    {
        if((fp=fopen("userdata.txt","wb+"))==NULL)
        {
            printf("Can't create or open Database.");
            return 0;
        }
    }

    char id, pwd, role;
    while (fscanf(fp, "%*s %*s %s ", role) == 1)
    {
        if (strcmp(role, "admin") == 0) {
            admin();
        } else if (strcmp(role, "student") == 0) {
            student();
        } else if (strcmp(role, "coordinator") == 0) {
            coordinator();
        } else if (strcmp(role, "leader") == 0) {
            leader();
        }
    }
}
