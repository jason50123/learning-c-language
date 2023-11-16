#include <stdlib.h>
#include <stdio.h>


int main(){
    
    int matrix[2][3] = {{1,2,3},{4,5,6}};
    
    printf("%d %d %d %d %d %d \n",&matrix[0][0],&matrix[0][1],&matrix[0][2],&matrix[1][0],&matrix[1][1],&matrix[1][2]);
    
    
    printf("%d %d %d %d %d %d \n", *(matrix + 0) + 0,*(matrix + 0) + 1,*(matrix + 0) + 2,
                                    *(matrix + 1) + 0,*(matrix + 1) + 1,*(matrix + 1) + 2);


    int(*ptr2D)[3] = matrix;

    printf("%d\n", ptr2D[0][1]);
    printf("%d\n",sizeof(matrix));

    int *ptr1Darr = matrix[0];
    printf("%d\n", *(ptr1Darr)+5);

}