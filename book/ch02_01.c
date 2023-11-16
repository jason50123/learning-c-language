#include <stdio.h>
#include <stdlib.h>

int main(){
    int Score[5] = {12, 43, 23, 89, 82};
    int i = sizeof(Score)/sizeof(Score[0]);
    printf("%d",i);
    for( int j = 0; j<i; j++){
        printf("the score %d is : %d \n", i,Score[j]);
    }
    return 0;
}
