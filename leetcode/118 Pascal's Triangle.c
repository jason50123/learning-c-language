#include <stdio.h>
#include <stdlib.h>


int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    int **out_array = (int**) malloc(sizeof(int*) * numRows);
    *returnColumnSizes = (int*) malloc(sizeof(int) * numRows);
    *returnSize = numRows;

    for(int i = 0; i < numRows ; i++){
        (*returnColumnSizes)[i] = i + 1;
        out_array[i] = (int*)malloc(numRows * sizeof(int));
        out_array[i][0] = 1;
        out_array[i][i] = 1;
    }
    for(int i = 0; i < numRows; i++){
        for(int j = 1; j <i ;j++){
            out_array[i][j] = out_array[i-1][j-1] + out_array[i-1][j];
        }
    }
    
    return out_array;
}