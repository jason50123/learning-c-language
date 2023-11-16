#include <stdio.h>

typedef struct {
    
    int a;
    char b;
    char c;
}Size1;

typedef struct {
    
    char b;
    int a;
    char c;
}Size2;

typedef struct {
    char b;
    char c;
    double a;
}Size3;

typedef struct {
    char b;
    double a;
    char c;
    
}Size4;


int main(){

    printf("%d\n",sizeof(Size1));
    printf("%d\n",sizeof(Size2));
    printf("%d\n",sizeof(Size3));
    printf("%d\n",sizeof(Size4));
    return 0;
}