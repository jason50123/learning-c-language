#include <stdio.h>
#include <sdlib.h>

struct student {
    char name[20];
    int score;
    struct student *next
}
typedef struct student s_data;
s_data *ptr; /*�s������*/
s_data *head; /*��C�}�Y����*/
s_data *new_data; /*�s�W�����Ҧb��m����*/

head = (s_data*) malloc(sizeof(s_data));
ptr = head;
ptr->next = NULL;
do{
    printf("(1)�s�W (2)���} =>");
    scanf("%d",&select);
    if (select != 2){
        printf("�m�W �Ǹ� �ƾǦ��Z �^�妨�Z")
        scanf("%s %s %d %d ")
    }
}
