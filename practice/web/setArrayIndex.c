#include <stdio.h>
#include <stdlib.h>

void set2dArrayIndex(int (*array)[], int row, int column, int modify);
void setVectorIndex(int *array, int element, int modify);

void setVectorIndex(int *array, int element, int modify){
    for(int i = 0 ; i<element; i++){
        *(array+i) =modify; 
    }
}

void set2dArrayIndex(int (*array)[3], int row, int column, int modify){
    for(int i = 0; i< row; i++){
        for(int j = 0; j< column; j++){
            *(array +i *column + j) = modify;
        }
    }
}
int main(){

    int vector[] = {1,2,3,4,5};
    setVectorIndex(vector, sizeof(vector)/sizeof(int), 6);
    for(int i = 0; i<sizeof(vector)/sizeof(int); i++){
        printf("this is %dth element, it's %d \n",i,*(vector+i));
    }
    int Arr2d[2][3] = {{1,2,3},{4,5,6}};
    int rows = sizeof(Arr2d)/sizeof(Arr2d[0]);
    int cols = sizeof(Arr2d[0])/sizeof(Arr2d[0][0]);
    set2dArrayIndex(Arr2d, rows, cols,9);
    for(int i = 0; i<rows; i++){
        for(int j = 0 ; j < cols; j++){
            printf("this is %d %dth element, it's %d \n",i,j,*(Arr2d+i +j* rows));
        }
        
    }
    
    return 0;
}