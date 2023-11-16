#include <stdio.h>

int y = 1;

void foo(){
    static int x = 4;
    int z =10;

    x++;
    y++;
    z++;
    printf("static x = %d global y = %d localz = %d \n", x, y, z);
}

int main(){
    foo();

    y++;
    printf("%d\n",y);
    foo();
}