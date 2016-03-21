#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct class{
    int grade;
    char classId[20];    
};
struct student{
    int id;
    char name[50];
    struct class classfd; 
};

int main(){
    struct student A;
    A.id = 1;
    strcpy(A.name,"Hai Nguyen Hoang");
    A.classfd.grade = 9;
    strcpy(A.classfd.classId,"KSTN-K56");
    printf("A.name: %s\r\n",A.name);
    return 0;
}
