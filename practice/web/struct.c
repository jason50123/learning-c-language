#include <stdio.h>


struct Student{
    char name[20];
    char major[20];
    int age;
};

struct School{
    char name[20];
    float PR;
    struct Student student;
};


void show_student(struct Student people){
    printf("name = %s , major = %s, age = %d", people.name, people.major, people.age);
}

int main(){
    struct School NTU = {"NTU", 99.5, {"Jack", "CS", 20}};
    printf("name = %s, \n",NTU.name);
    printf("HELLO = %s\n",NTU.student.major);
    struct Student Hank = {"Hank","CS", 20};
    
    show_student(Hank);
    return 0;
}