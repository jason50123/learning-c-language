#include <stdio.h>
#include <sdlib.h>

struct student {
    char name[20];
    int score;
    struct student *next
}
typedef struct student s_data;
s_data *ptr; /*存取指標*/
s_data *head; /*串列開頭指標*/
s_data *new_data; /*新增元素所在位置指標*/

head = (s_data*) malloc(sizeof(s_data));
ptr = head;
ptr->next = NULL;
do{
    printf("(1)新增 (2)離開 =>");
    scanf("%d",&select);
    if (select != 2){
        printf("姓名 學號 數學成績 英文成績")
        scanf("%s %s %d %d ")
    }
}
