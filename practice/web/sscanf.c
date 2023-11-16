#include <stdio.h>

int main(){
    char str[5];
    int dec;
    float pi;
    char input[20] ;
    scanf("%s%d%f", str, &dec, &pi);
    sscanf(input,"%s%d%f", str, &dec, &pi);
    printf("out = %s %d %f \n",str, dec, pi);
    return 0 ;
}