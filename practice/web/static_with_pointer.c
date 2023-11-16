#include <stdio.h>

int y = 1;

void foo(){
    static int x = 4;
    int z =10;

    x++;
    y++;
    z++;
    printf("static x = %p global y = %p localz = %p \n", &x, &y, &z);
}

int main(){

    printf("foo = %p main = %p \n",foo,main);

}