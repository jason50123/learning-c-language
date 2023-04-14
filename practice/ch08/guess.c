#include <stdio.h>

int main(void){
    int guess = 1;
    char response ;

    printf("Pick an integer from 1 to 100, i will try and get it");
    printf("it \n Respond with a y if  my guess is right and with");
    printf("\n an n if it was wrong, \n");
    printf("Uh ... is your number %d?\n",guess);
    
    while((response = getchar()) != 'y'){
        if(response == 'n')
            printf("well, then, is it %d \n",++guess);
        else
            printf("Sorry ,i only understand y or n\n");
        
        while(getchar() != '\n')
            continue;
    }
        
    printf("i know i could didit.\n");
    return 0;
}