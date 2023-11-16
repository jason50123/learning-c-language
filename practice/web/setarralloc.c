#include <stdio.h>
#include <stdlib.h>

setArrayValue(int *arr, int size, int value){
    for( int i = 0; i< size; i++){
        arr[i] = value;
    }
}


int main(){

    int *vector1D = (int *)malloc(sizeof(int) * 5);
    setArrayValue(vector1D,5,30);
    for(int i = 0 ; i<5; i++){
        printf("%d\n",*(vector1D+i));
    }
    free(vector1D); // ÄÀ©ñ°O¾ÐÅé

    return 0;

}