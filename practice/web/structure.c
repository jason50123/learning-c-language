#include<stdio.h>

typedef struct{
    int id;
    char name[7];
}Zoo;

int main(){
    
    Zoo z1 = {0, "Monkey"};
    Zoo *zPtr1 = &z1;

    Zoo z[3] = {{1,"Dog"},{2,"cat"},{3,"turtle"}};
    Zoo *zptr2 = z;

    for( int i = 0; i < sizeof(z)/sizeof(Zoo); i++){
        printf("%d %s \n", zptr2[i].id,zptr2[i].name);
        //-> 等同*()
        printf(" %d %s \n", (zptr2+ i )-> id,(zptr2+ i )-> name);
    }

    printf("%d %s \n",(*zPtr1).id,(*zPtr1).name);
    //等價於下面
    printf("%d %s \n",zPtr1->id,zPtr1 -> name);
    return 0;
}