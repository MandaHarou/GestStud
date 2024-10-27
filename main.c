#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//***************
#define MAX 100
#define NOTEMAX 10
//***************
#include "Function.h"
#include "Database.h"
//***************
static int SID = 1;
static void initialize(Student *p);
int main()
{
    int edit_x, remove_x, x;
    int choice[MAX];
    Student stud;
    char name_x[MAX];
//********************
//********************
    edit_x = 0;
    remove_x = 0;
    initialize(&stud);
    while(1)
    {
        system("cls");
        system("color 2");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t  ""      |t1-New Student\t""                                |\n");
        printf("\t\t\t\t\t\t|2-Display bulletin\t""                        |\n");
        printf("\t\t\t\t\t\t|3-Edit name\t""                                |\n");
        printf("\t\t\t\t\t\t|4-Remove a student\t" "                        |\n");
        printf("\t\t\t\t\t\t|5-Display the class average and student aprove\t""|\n");
        printf("\t\t\t\t\t\t|6-Exit the program\t\t\t\t|\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t|Enter your choice: ");
        scanf("%d",&choice[1]);
        printf("\n");
        switch(choice[1])
        {
        case 1:
            do {
                printf("Enter the student's last name: ");
                scanf("%s", stud.name);
                printf("\n");
                printf("Enter the student's first name: ");
                scanf("%s", stud.firstname);
                printf("\n");
                printf("Enter the student's grade: ");
                scanf("%d", &stud.gradeS);
                addstud(&stud);
                printf("\n");
                printf("Do you want to add more? Enter 1 for yes: ");
                scanf("%d", &choice[2]);
                printf("\n");
            } while(choice[2] == 1);
            break;
        case 2:
            printf("Would you like to use 1: SID or 2: name: ");
            scanf("%d", &choice[3]);
            if(choice[3] == 1)
            {
                printf("Please enter the SID: ");
                scanf("%d",&x);
                display_ID(&x);
            }
            else if(choice[3] == 2)
            {
                printf("Enter the name: ");
                scanf("%s",name_x);
                display_chr(name_x);
            }
            else
            {
                exit(1);
            }
            break;
        case 3:
            printf("Please enter the SID: ");
            scanf("%d", &edit_x);
            display_ID(&edit_x);
            printf("\n");
            edit(&edit_x);
            break;
        case 4:
            printf("Please enter the SID: ");
            scanf("%d", &remove_x);
            remove_stud(&remove_x);
            break;
        case 5:
            average_class();
            break;
        case 6:
            printf("Thank you for using this software!\n");
            exit(1);
            break;
        default:
            printf("Invalid option. Try again.\n");
            break;
        }
        printf("To return to the menu, enter 1. To quit the program, enter 0: ");
        scanf("%d", &choice[4]);
        if (!choice[4]) exit(1);
    }

    return 0;
}

void addstud(Student* s)
{
    FILE *record = fopen("bulletin.db", "a+");
    int code;
    int temp = 0;
    char temp_name[100], temp_firstname[100];
    int temp_gradeS;
    if (record == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }
    while (fscanf(record, "%d\n%s\n%s\n%d\n", &code, temp_name, temp_firstname, &temp_gradeS) == 4)
    {
        if (code == SID)
        {
            SID++;
        }
        else if (code > SID)
        {
            temp = code - SID;
            code += temp;
            SID = code;
        }
    }
    printf("Total number of students: %d", SID);
    fprintf(record, "%d\n%s\n%s\n%d\n", SID, s->name, s->firstname, s->gradeS);
    fclose(record);
}

void display_ID(int* ID)
{
    int c;
    c = *ID;
    FILE *record = fopen("bulletin.db", "r");
    char temp_name[100], temp_firstname[100];
    int temp_gradeS, cod;
    if (record == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }
    while(fscanf(record, "%d\n%s\n%s\n%d\n", &cod, temp_name, temp_firstname, &temp_gradeS) == 4)
    {
        if(cod == c)
        {
            printf("SID:%d\nName:%s\nFirstName:%s\nAverage:%d\n", cod, temp_name, temp_firstname, temp_gradeS);
        }
    }
    fclose(record);
}

void display_chr(char* x)
{
    FILE *record = fopen("bulletin.db", "r");
    char temp_name[100], temp_firstname[100];
    int temp_gradeS, cod;
    if (record == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }
    while(fscanf(record, "%d\n%s\n%s\n%d\n", &cod, temp_name, temp_firstname, &temp_gradeS) == 4)
    {
        if(strcmp(x, temp_name) == 0)
        {
            printf("SID:%d\n Name:%s\n FirstName:%s\n Average:%d\n", cod, temp_name, temp_firstname, temp_gradeS);
        }
    }
    fclose(record);
}

void edit(int* ID)
{
    int c;
    c = *ID;
    FILE* record = fopen("bulletin.db", "r");
    FILE* ftemp = fopen("temp.db", "w");
    char temp_name[100], temp_firstname[100];
    int temp_gradeS, cod;
    if (record == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }
    if (ftemp == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }
    while (fscanf(record, "%d\n%s\n%s\n%d", &cod, temp_name, temp_firstname, &temp_gradeS) == 4)
    {
        if (cod == c)
        {
            printf("Enter the new name: ");
            scanf("%s", temp_name);
        }
        fprintf(ftemp, "%d\n%s\n%s\n%d\n", cod, temp_name, temp_firstname, temp_gradeS);
    }
    fclose(ftemp);
    fclose(record);
    remove("bulletin.db");
    rename("temp.db", "bulletin.db");
}

void remove_stud(int* ID)
{
    int c;
    c = *ID;
    FILE* record = fopen("bulletin.db", "r");
    FILE* ftemp = fopen("temp.db", "w");
    char temp_name[100], temp_firstname[100];
    int temp_gradeS, cod;
    if (record == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }
    if (ftemp == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }
    while (fscanf(record, "%d\n%s\n%s\n%d", &cod, temp_name, temp_firstname, &temp_gradeS) == 4)
    {
        if (cod != c)
        {
            fprintf(ftemp, "%d\n%s\n%s\n%d\n", cod, temp_name, temp_firstname, temp_gradeS);
        }
    }
    fclose(ftemp);
    fclose(record);
    remove("bulletin.db");
    rename("temp.db", "bulletin.db");
}

void average_class(void)
{
    char temp_name[100], temp_firstname[100];
    int temp_gradeS, cod, i = 0;
    FILE* record = fopen("bulletin.db", "rt");
    if (record != NULL)
    {
        while (fscanf(record, "%d\n%s\n%s\n%d", &cod, temp_name, temp_firstname, &temp_gradeS) == 4)
        {
            i++;
        }
        rewind(record);
        while (fscanf(record, "%d\n%s\n%s\n%d", &cod, temp_name, temp_firstname, &temp_gradeS) == 4)
        {
            printf("%d\n%s\n%s\n%d\n%.2f\n", cod, temp_name, temp_firstname, temp_gradeS, cal_average(i, temp_gradeS));
        }
        rewind(record);
        printf("****************************Aprove list*************************************\n");
        while (fscanf(record, "%d\n%s\n%s\n%d", &cod, temp_name, temp_firstname, &temp_gradeS) == 4)
        {
            if(temp_gradeS >= NOTEMAX)
            {
                printf("student numb %d is aproved \n Name: %s\n Average: %d\n\n", cod, temp_name, temp_gradeS);
            }
        }

    }
    fclose(record);
}
double cal_average(int x, int y)
{
    return (double)y / x;
}
static void initialize(Student *p)
{
    strcpy(p->name, "");
    strcpy(p->firstname, "");
    p->gradeS = 0;
}
