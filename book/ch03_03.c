#include <stdio.h>
#include <stdlib.h>


struct employee{
    int num,salary;
    char name[10];
    struct employee *next;
};

typedef struct employee emp_s;

int main(){

    int select,num =0;

    emp_s *ptr;
    emp_s *head;
    emp_s *new_data;

    head = (emp_s *)malloc(sizeof(emp_s));
    head ->next = NULL;
    ptr = head;
    do{
        printf("(1)前面(2)中間(3)後面(4)離開");
        scanf("%d",select);
        if(select != 4){
            switch (select)
            {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                printf("請輸入:工號 薪水 名字");
                new_data = (emp_s *)malloc(sizeof(emp_s));
                scanf("%d %d %s", &ptr->num,&ptr->salary,ptr->name);
                ptr ->next = new_data;
                new_data -> next = NULL;
                ptr = ptr->next;
                break;
            
            default:
                break;
            }
            
            if(select == 3){

            }
            
        }
        
    }

    return 0;
}