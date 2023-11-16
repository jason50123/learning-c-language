#include <stdio.h>
#include<stdlib.h>

void assignMem(int **p){
    printf("%p\n", &p);
    *p = (int *)malloc(sizeof(int));
    printf("*pªº¼Æ­È= %p \n",*p);
    **p = 10;
};

int main(){
    int *p = NULL;
    assignMem(&p);
    printf("%d\n", *p);
}