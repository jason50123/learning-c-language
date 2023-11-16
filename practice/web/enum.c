#include <stdio.h>

enum DAY{
    //預設為0,1,2...下去，不過也可以中途改某一個數字後面的就會跟著累加
    saturday,
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday
};

int main(){
    printf("%d", saturday);
    return 0;
};