#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct waiting{
    char name[20]; //이름 
    char number[20]; //연락처 
    int people; //인원수 
    struct wating* next; //다음 노드 정보 
} waiting_t;

int menu();
void addWaiting();
void delWaiting(); 

int main(){
    while(1){
        switch(menu()){
            case 1:
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
        }
    }
    return 0; 

}

int menu(){
    int choice;
    printf("<숭실음식점 대기 관리 프로그램>");
    printf("===========================\n");
    printf("1.대기 등록\n");
    printf("2.대기 삭제\n");
    printf("3.대기 손님 정보 수정\n");
    printf("4.대기시간 조회\n");
    printf("5.음식 주문\n");
    printf("6.전체 대기 목록 출력\n");
    printf("7.파일에 저장\n");
    printf("8.파일 업로드하기\n");
    printf("9.종료\n");
    printf("===========================\n");
    printf("번호를 선택해주세요: ");
    scanf("%d", &choice);
    return choice; 
}
