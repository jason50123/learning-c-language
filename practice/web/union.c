# include <stdio.h>

typedef union{
    int a;
    float b;
    char c;
}Sample;

int main(){
    //union�|�@�Τ@���O����ҥH�|�Q�\��
    Sample s = {10,15.3,'a'};
    printf("%d %f %d\n", s.a,s.b, s.c);
    return 0;
}