#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct waiting{
    char name[20]; //이름 
    char number[20]; //연락처 
    int people; //인원수 
    struct wating* next; //다음 노드 정보 
} waiting_t;

//함수선언 
int menu();
void addWaiting(waiting_t** head, void(*func_show)(waiting_t*));
void delWaiting(waiting_t** head, waiting_t*(*func_search)(waiting_t*,char*)); 
void show(waiting_t* node);
waiting_t* search(waiting_t* head, char number[20]);
void printWaitingList(waiting_t *head);

int main(){

    waiting_t* head = NULL;
    while(1){
        switch(menu()){
            case 1:
                addWaiting(&head,show);
                break;
            case 2:
                delWaiting(&head,search);
                break;
            case 5:
                printWaitingList(head);
                break;
        }
    }
    return 0; 

}

int menu(){
    int choice;
    printf("\n\n<숭실음식점 대기 관리 프로그램>\n");
    printf("===========================\n");
    printf("1.대기 등록\n");
    printf("2.대기 삭제\n");
    printf("3.대기 손님 정보 수정\n");
    printf("4.대기시간 조회\n");
    printf("5.전체 대기 목록 출력\n");
    printf("6.파일에 저장\n");
    printf("7.파일 업로드하기\n");
    printf("8.종료\n");
    printf("===========================\n");
    printf("번호를 선택해주세요: ");
    scanf("%d", &choice);
    return choice; 
}

void addWaiting(waiting_t** head,void(*func_show)(waiting_t*)){
    char name[20];
    char number[20];
    int people;
    waiting_t* new_node; 

    printf("이름: ");
    scanf("%s",name);
    printf("전화번호: ");
    scanf("%s", number);
    printf("인원수: ");
    scanf("%d", &people);

    new_node = (waiting_t*)malloc(sizeof(waiting_t));
    strcpy(new_node->name, name);
    strcpy(new_node->number, number);
    new_node->people = people; 
    new_node->next = NULL;
    if (*head == NULL)
        *head = new_node;
    else{
        waiting_t *tmp = *head;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
    printf("=========================\n");
    func_show(new_node);
    printf("대기가 등록되었습니다.\n"); 
}

void show(waiting_t* node){
    printf("이름\t 전화번호\t 인원수\n");
    printf("%s\t %s\t %d명\n",node->name, node->number, node->people);
}

void delWaiting(waiting_t** head, waiting_t* (*func_search)(waiting_t*,char*)){
    char number[20];
    int ans;
    waiting_t* tmp_node;
    waiting_t* temp;
    waiting_t* pre;
    temp = *head; 

    printf("등록한 전화번호를 입력해주세요 : ");
    scanf("%s", number);
    tmp_node = func_search(*head,number);
    if(tmp_node==NULL){
        printf("등록되지 않은 번호입니다.\n");
        return; 
    }
    printf("대기를 삭제하시겠습니까?(1: 네 2: 아니오 )\n");
    scanf("%d", &ans);
    if(ans==1){
        if(strcmp(temp->number,number)==0){
            *head = temp->next; //가장 앞에 있는 노드 삭제할때 
            free(temp);
            printf("대기 삭제되었습니다.\n");
        }
        else{
            while(temp!=NULL){
                if(strcmp(temp->number,number)==0){
                    pre->next = temp->next;
                    free(temp);
                    printf("대기가 삭제되었습니다.\n");
                    break;
                }
                pre = temp;
                temp = temp->next;
            }
        }
    }
    else if(ans==2){
        printf("대기 삭제를 취소합니다.\n");
    }
    else{
        printf("잘못된 입력입니다.\n");
    }
}

waiting_t* search(waiting_t* head, char number[20]){ //등록된 전화번호를 가진 노드를 리턴한다. 
    waiting_t* tmp = head;
    while(tmp != NULL){
        if( strcmp(tmp->number,number)==0)
            return tmp;
        tmp = tmp -> next;
    }
    return NULL;
}

void printWaitingList(waiting_t *head){
    waiting_t *temp = head;
    int i = 1; 
    if(head = NULL){
        printf("대기가 없습니다.\n");
    }
    while(temp!=NULL){
        printf("대기순서\t이름\t 전화번호\t 인원수\n");
        printf("%d\t %s\t %s\t %d명\n",i, temp->name, temp->number, temp->people);
        i++;
        temp= temp->next;
    }
}

