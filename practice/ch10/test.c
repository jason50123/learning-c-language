#include <stdio.h>
#define MONTHS 12
//可以把陣列改成唯讀 -> const int days[MONTHS] 
int main(void){
    int days[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int index;
    
    for (index = 0; index <MONTHS; index++)
        printf("MONTHS %d has %2d days.\n",index +1,days[index]);
}