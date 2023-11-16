#include <stdio.h>

int main(){
    
    int *p1 =NULL;
    int **p2;
    p2 = &p1;
    *p2 = (int*)malloc(sizeof(int));

    
    return 0;

}