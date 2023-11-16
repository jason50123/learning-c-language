#include <stdio.h>
#include <stdlib.h>

int main(){
    int select, student_no = 0, num = 0;
    float Msum = 0, Esum = 0;
    
    struct student{
        char name[20];
        int Math;
        int Eng;
        char no[10];
        struct student *next;
    };
    typedef struct student s_data;
    s_data *ptr;
    s_data *head;
    s_data *new_data;

    head = (s_data*)malloc(sizeof(s_data));
    head ->next = NULL;
    ptr = head;
    do{
        printf("(1)新增 (2)離開 =>");
        scanf("%d", &select);
        if(select != 2){
            printf("姓名 學號 數學成績 英文成績: ");
            new_data = (s_data*)malloc(sizeof(s_data));
            scanf("%s %s %d %d",new_data -> name, new_data->no,&new_data->Math, &new_data -> Eng);
            ptr -> next = new_data;
            new_data -> next = NULL;
            ptr = ptr -> next;
            num++;

        }

    }while(select != 2);
    ptr = head->next;
    putchar('\n');
    while(ptr!=NULL){
        printf("姓名: %s\t 學號: %s\t數學成績: %d\t 英文成績: %d\t",ptr->name, ptr->no, ptr->Math, ptr ->Eng);
        Msum += ptr ->Math;
        Esum += ptr ->Eng;
        student_no++;
        ptr = ptr->next;
    }
    printf("========================\n");
    printf("本串列學生數學平均: %.2f 英文成績平均: %.2f\n",Msum/student_no,Esum/student_no);
    system("pause");
    return 0;

}