#include <stdio.h>
#include <stdlib.h>

void setArrayValue (int *arr, int size, int value){
    for(int i = 0; i < size ; i++){
        arr[i] = value;
    }
}

void set2DArray(int (*arr)[3], int sizex, int sizey, int value){
    for(int i = 0; i< sizex; i++){
        for(int j = 0; j < sizey; j++){
            arr[i][j] = value;
        }
    }
}

int main(){
    int vector[] = {1,2,3,4,5};
    setArrayValue(vector,5,45);
    for (int i = 0; i<5; i++){
        printf("%d \n",vector[i]);
    }
    int matrix[2][3] = {{1,2,3},{4,5,6}};
    set2DArray(matrix,2,3,33);
    
    for (int i = 0; i<2; i++){
        for(int j = 0; j<3 ; j++){
            printf("%d \n",matrix[i][j]);
        }
    }    
}