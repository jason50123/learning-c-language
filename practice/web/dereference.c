#include <stdio.h>

int y = 1;

void foo(){
    static int x = 4;
    int z =10;


    printf("static x = %p global y = %p local z = %p \n", &x, &y, &z);
    int *x_ptr;
    int *y_ptr;
    int *z_ptr;

    x_ptr = &x;
    y_ptr = &y;
    z_ptr = &z;

    //�o�˷Q�|�ܦ��a�}���[�Adereference *x_ptr ++
    //�n�g���o��(*x_ptr)++
    printf("static x = %d global y = %d local z = %d \n", *x_ptr, *y_ptr, *z_ptr);
}

int main(){
    foo();
    printf("foo = %p main = %p \n",foo,main);

}