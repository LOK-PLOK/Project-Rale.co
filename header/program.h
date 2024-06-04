#ifndef TODO_HEADER
#define TODO_HEADER
// User datatypes and function prototypes FILE

#define MAX 31 //including '\0'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#define flush fflush(stdin)

typedef enum{
    READ, ADD, EDIT, DELETE, CLOSE
}Option;

typedef enum{
    UNFINISHED,PENDING,DONE,OTW,DELIVERED
}Status;

typedef enum{
    Small, Medium, Large, XLarge, XXLarge, XXXLarge
}Size;

typedef enum{
    RANDOM,RESIST,DEVOTION,PANTONE,HAPPYH,EXEMPLIFY,TEACHP,DQUIT,SINULOG
}Design;

typedef enum{
    RANDOMIZE,WHITE,BLACK,PURPLE,GREEN,RED,BLUE
}Color;

typedef struct{
    char Fname[26];
    char Lname[16];
    char Name[50];// Lname + Fname;
}Name;

typedef struct{
    int cust_id;
    Name cust;
    char email[50];
    Design design;
    Color color;
    Size size;
    int quantity;
    Status status;
}Order;

typedef struct node{
    Order order;
    struct node* next;
}*List;


FILE* openFile();
List getList(FILE* fptr);
Option landingScreen();
void doOption(Option,List*,FILE**);
void displayOrder(List head);
int isGmail(char *email);
void capital(char* Name);
Order createOrder(List* head);
void addOrder(List* head);
List tobeEdited(List head, int id);
void editOrder(List head);
void editName(List edit);
void editEmail(List edit);
void editDesign(List edit);
void editColor(List edit);
void editSize(List edit);
void editQuantity(List edit);
void editStatus(List edit);
void deleteOrder(List* head);
void freeAll(List head);
void save(FILE** file, List head);
void savetoCSV(List head,const char* filename);
void end(FILE *fptr, List head);
#endif