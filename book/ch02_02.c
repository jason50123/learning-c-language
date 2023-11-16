#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr[2][2];
    int sum;
    printf("| a1 b1 |\n");
    printf("| a2 b2 |\n");
    printf("請輸入a1\n");
    scanf("%d",&arr[0][0]);
    printf("請輸入b1\n");
    scanf("%d",&arr[0][1]);
    printf("請輸入a2\n");
    scanf("%d",&arr[1][0]);
    printf("請輸入b2\n");
    scanf("%d",&arr[1][1]);
    sum = arr[0][0]*arr[1][1];
    arr[0][1] = arr[0][1] *arr[1][0];
    sum -= arr[0][1];
    printf("行列式的值 : %d",sum);
    return 0;

}