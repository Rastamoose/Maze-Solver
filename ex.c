#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void maths(void);
void input(void);
void switchs(void);
int cmpstr(const char* a, const char* b);

struct Student{
    char name[50];
    char major[50];
    int age;
    double gpa;

};

int main(){

    struct Student student1;
    student1.age = 22;
    strcpy(student1.name, "Jim");

    return 0; 
}

void switchs(void){
    char grade = 'A';

    switch(grade){
        case 'A':
            printf("Top grade\n");
            break;
        default:
            printf("Bad\n");
            break;
    }
}

int cmpstr(const char* a, const char* b){
    // if not matching then break and false
    // if matching but reached \0 then break and true
    int i = 0;
    while(a[i]==b[i] && a[i]){
        i++;
    }      
    
    return (unsigned char)a[i]-(unsigned char)b[i];
}

void maths(void){
    // MATHS
    printf("%f\n", pow(2, 3));
    printf("%f\n", fmod(7,3));
    printf("%f\n", sqrt(9));
    printf("%.3f\n", M_PI); // dp
    printf("%.3g\n", M_PI); // sf
    printf("%f\n", fabs(-M_PI));    // abs
}

void input(void){
    // INPUT
    char name[20];
    printf("Enter your first name: ");
    scanf("%19s", name);      // only gets first part
    printf("Name: %s\n", name);

    // clear stream as enter press from scanf leaves \n in input buffer
    int c;
    while ((c=getchar()) != '\n' && c!=EOF);

    printf("Enter your full name: ");
    // get whole input string inc spaces
    fgets(name, sizeof(name), stdin);            
    printf("Name: %s\n", name);

}