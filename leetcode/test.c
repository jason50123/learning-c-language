int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    int **out_array = (int**) malloc(sizeof(int*) * numRows);
    *returnColumnSizes = (int*) malloc(sizeof(int) * numRows);
    *returnSize = numRows;

    for (int i = 0; i < numRows; i++) {
        out_array[i] = (int*) malloc((i + 1) * sizeof(int));
        (*returnColumnSizes)[i] = i + 1;

        for (int j = 0; j < i + 1; j++) {
            if (j == 0 || j == i)
                out_array[i][j] = 1;
            else 
                out_array[i][j] = out_array[i - 1][j - 1] + out_array[i - 1][j];
        }
    }
    return out_array;
}