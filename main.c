#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WAITING_TIME 20 //한팀당 예상 대기시간  

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
void modifyWaiting(waiting_t *head, waiting_t*(*func_search)(waiting_t*,char*), void(*func_show)(waiting_t*));
void printWaitingTime(waiting_t *head, waiting_t*(*func_search)(waiting_t*,char*));
void save(waiting_t* head);
void load(waiting_t** head);

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
            case 3:
                modifyWaiting(head,search,show);
                break;
            case 4:
                printWaitingTime(head,search);
                break;
            case 5:
                printWaitingList(head);
                break;
            case 6:
                save(head);
                break;
            case 7:
                load(&head);
                break;
            case 8:
                printf("프로그램을 종료합니다\n");
                printf("===================================\n\n");
                return 0; 
            default: 
                printf("잘못된 입력입니다.\n");
                break;
        }
    }
    return 0; 
}

//메뉴 출력하는 함수 
int menu(){
    int choice;
    printf("\n\n<숭실음식점 대기 관리 프로그램>\n");
    printf("===================================\n");
    printf("1.대기 등록\n");
    printf("2.대기 삭제\n");
    printf("3.대기 손님 정보 수정\n");
    printf("4.대기시간 조회\n");
    printf("5.전체 대기 목록 출력\n");
    printf("6.파일에 저장\n");
    printf("7.파일 업로드하기\n");
    printf("8.종료\n");
    printf("===================================\n");
    printf("번호를 선택해주세요: ");
    scanf("%d", &choice);
    return choice; 
}

//대기 등록하는 함수 
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
    printf("===================================\n");
    func_show(new_node);
    printf("대기가 등록되었습니다.\n"); 
}

//한 노드의 정보를 출력하는 함수 
void show(waiting_t* node){
    printf("이름\t 전화번호\t 인원수\n");
    printf("%s\t %s\t %d명\n",node->name, node->number, node->people);
}

//대기를 삭제하는 함수 
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
        if(strcmp(temp->number,number)==0){       //가장 앞에 있는 노드 삭제할때 
            *head = temp->next; 
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

//등록된 전화번호를 가진 노드를 리턴하는 함수 
waiting_t* search(waiting_t* head, char number[20]){  
    waiting_t* tmp = head;
    while(tmp != NULL){
        if( strcmp(tmp->number,number)==0)
            return tmp;
        tmp = tmp -> next;
    }
    return NULL;
}

//전체 대기 목록을 출력하는 함수 
void printWaitingList(waiting_t *head){
    waiting_t *temp = head;
    int i = 1; 
	
    if(head = NULL){
        printf("대기가 없습니다.\n");
    }
    printf("\n대기순서  이름\t 전화번호\t 인원수\n");
    while(temp!=NULL){
        printf("%d\t  %s\t %s\t %d명\n",i, temp->name, temp->number, temp->people);
        i++;
        temp= temp->next;
    }
}

//대기 정보를 수정하는 함수 
void modifyWaiting(waiting_t *head, waiting_t*(*func_search)(waiting_t*,char*),void(*func_show)(waiting_t*)){    
    char number[20],mod_name[20],mod_number[20];
    waiting_t* tmp_node;
    int choice, mod_people;

    printf("등록한 전화번호를 입력해주세요 : ");
    scanf("%s", number);
    tmp_node = func_search(head,number);
    if(tmp_node==NULL){
        printf("등록되지 않은 번호입니다.\n");
        return; 
    }
    printf("등록된 정보입니다.\n");
    func_show(tmp_node);
    printf("===================================\n");
    printf("수정할 내용을 선택하세요(1: 이름 2: 전화번호 3: 인원수)\n");
    scanf("%d", &choice);
    switch(choice){
			case 1:
				printf("수정할 내용을 입력하세요: ");
				scanf("%s",mod_name);
				strcpy(tmp_node->name,mod_name);
				break;
			case 2:
				printf("수정할 내용을 입력하세요: ");
				scanf("%s",mod_number);
				strcpy(tmp_node->number,mod_number);
				break;
			case 3:
				printf("수정할 내용을 입력하세요: ");
				scanf("%d",&mod_people);
				tmp_node->people=mod_people;
				break;
			default:
				printf("잘못 입력하셨습니다.\n");
				break;
    }
    printf("===================================\n");
	printf("다음과 같이 수정되었습니다.\n");
	show(tmp_node);
}

//전화번호를 조회해 현재 대기순서와 대기시간을 출력하는 함수 
void printWaitingTime(waiting_t *head, waiting_t*(*func_search)(waiting_t*,char*)){
    char number[20];
    waiting_t* tmp_node;
    waiting_t* temp = head; 
    int num=0;
    
    printf("등록한 전화번호를 입력해주세요 : ");
    scanf("%s", number);
    tmp_node = func_search(head,number);
    if(tmp_node==NULL){
        printf("등록되지 않은 번호입니다.\n");
        return; 
    }
    while(temp!=NULL){
        num++;
        if(strcmp(temp->number,number)==0){
            break;
        }
        temp= temp->next;
    }
    printf("%s님은 현재 대기 %d번째이고, 예상 대기 시간은 %d분입니다.\n", tmp_node->name, num, num*WAITING_TIME);
}

//노드의 정보를 파일에 저장하는 함수 
void save(waiting_t* head){
    waiting_t* node = head;
    FILE* fp = fopen("waiting.txt", "w");
    if(fp==NULL){
        printf("파일을 열 수 없습니다.\n");
        return; 
    }
    while(node!=NULL){
        fprintf(fp, "%s %s %d\n", node->name, node->number, node->people);
        node = node-> next;
    }
    fclose(fp);
    printf("파일을 저장했습니다.\n");
}

//파일의 데이터를 구조체로 변환하는 함수 
void load(waiting_t** head){
    waiting_t* node;
	FILE* fp=fopen("waiting.txt","r+");
	if(fp==NULL){
		printf("파일을 열 수 없습니다.\n");
		return NULL;
	}
	while(1){
		node=(waiting_t*) malloc (sizeof(waiting_t));
        node->next = NULL;
		if(feof(fp)!=0)
			break;
		fscanf(fp,"%s %s %d\n", node->name, node->number, &node->people);
        if (*head == NULL)
            *head = node;
        else{
            waiting_t *tmp = *head;
            while (tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next =node;
        }
	}
	fclose(fp);
}
