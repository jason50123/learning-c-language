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
        printf("(1)�s�W (2)���} =>");
        scanf("%d", &select);
        if(select != 2){
            printf("�m�W �Ǹ� �ƾǦ��Z �^�妨�Z: ");
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
        printf("�m�W: %s\t �Ǹ�: %s\t�ƾǦ��Z: %d\t �^�妨�Z: %d\t",ptr->name, ptr->no, ptr->Math, ptr ->Eng);
        Msum += ptr ->Math;
        Esum += ptr ->Eng;
        student_no++;
        ptr = ptr->next;
    }
    printf("========================\n");
    printf("����C�ǥͼƾǥ���: %.2f �^�妨�Z����: %.2f\n",Msum/student_no,Esum/student_no);
    system("pause");
    return 0;

}