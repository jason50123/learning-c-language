#include <stdio.h>


typedef struct Position3D{
    float x,y,z;
}Point3D;

typedef struct{
    char color[20];
    int gears;
    int height;
}Bike;

typedef struct{
    int number;
    int speed;
    Bike b;
}Transportation;

int main(){
    Point3D p ={10.5, 20, 30.6};

    printf("%f %f %f",p.x,p.y,p.z);

    Bike b = {.height = 20, .gears = 21};
    printf("\n %d",b.height);

    Transportation t = {1, 10,{.height = 10}};
    printf("\n%d , %d", t.number,t.b.height);
}