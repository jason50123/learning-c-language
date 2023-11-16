#include <stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct island{
    
    char *name;
    int opens;

    struct island *next;

}Island;

Island *create(char *name, int opens){
    Island *i = (Island*)malloc(sizeof(Island));
    i -> name = name;
    i -> opens = opens;
    i ->next = NULL;
    return i;
}

void displayIsland(Island *ptr){
    Island *temp;
    temp = ptr;
    while(temp != NULL){
        
        printf("%s \n", temp->name);
        temp  = temp->next;
    }
    
}
/*void delNode(Island *first, char *target){
    Island *temp, *del;
    temp = first;
    while(temp != NULL){
        
        if(strcmp(temp -> next) ->name ,target) == 0){
            del = temp-> next;
            free(del);
            temp -> next = (temp->next) -> next;
        }
        printf("%s now and the next is %s\n", temp ->name,(temp -> next)->name);
        temp = temp -> next;
    }
    
}*/

void delNode(Island *start, char *target){
    Island *current = start;
    Island *pre = NULL;
    while(current != NULL && strcmp(current -> name, target) != 0){
        pre = current;
        current  = current -> next;
        
    }
    if(current == NULL){
        printf("notfound");
        return;
    }
    while(strcmp(current -> name, target) == 0){
        free(pre -> next);
        pre -> next = current ->next;
        current = pre ->next;
    }
    displayIsland(start);
}

int main(){
    /*
    Island i1 = {"i1",900,NULL};
    Island i2 = {"i2",600,NULL};
    Island i3 = {"i3",700,NULL};

    i1.next = &i2;
    i2.next = &i3;
    */

    Island *i1 = create("i1",900);
    Island *i2 = create("i2",600);
    Island *i3 = create("i3",800);
    Island *i4 = create("i4",750);
    Island *i5 = create("i5",1050);

    i1 ->next = i2;
    i2 -> next = i3;
    i3 -> next = i4;
    i4 -> next = i5;
    i5 -> next = NULL;
    
    //displayIsland(i1);
    delNode(i1,"i6");
    return 0;
}