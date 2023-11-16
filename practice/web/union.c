# include <stdio.h>

typedef union{
    int a;
    float b;
    char c;
}Sample;

int main(){
    //union會共用一塊記憶體所以會被蓋掉
    Sample s = {10,15.3,'a'};
    printf("%d %f %d\n", s.a,s.b, s.c);
    return 0;
}