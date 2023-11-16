#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    //1D
    char header[] = "mainplayer";
    header[0]= 'j';
    char *heaper = (char *)malloc(strlen("league of legend") + 1);
    strcpy(heaper,"league of legend");
    printf("%s",heaper);
    //2D
    char *tabHeader2D[3] ={"python","JS","C++"};

    char header2D[][11] = {"Python","c++","javascript"};//11那一格不能省略

    char **ptrHeader2D = (char**)malloc(sizeof(char*)*3);
    for(int i = 0; i < 3 ; i++){
        ptrHeader2D[i] = (char*)malloc(sizeof(char)*11);
    }
    strcpy(ptrHeader2D[0],"python");
    strcpy(ptrHeader2D[1],"JS");
    strcpy(ptrHeader2D[0],"Javascript");
    return 0;
}