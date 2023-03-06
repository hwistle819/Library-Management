#include "bpj.h"

extern BORROW** bkbrw;
extern int brcount;
extern BOOK** books;
extern int bkcount;
extern CLIENT** clients;
extern int stcount;

void clientlist(void)
{
    int i, num;

    puts(">>회원 목록<<\n");
    puts("1. 이름 검색  2. 학번 검색");
    puts("3. 전체 검색  4. 이전 메뉴\n");
    printf("번호를 입력하세요 : ");
    scanf("%d", &num);

    switch(num){
        case 1 :
            searchname();
            break;
        case 2 :
            searchnum();
            break;
        case 3 :
            searchall();
            break;
        case 4 :
            puts("이전으로 되돌아갑니다.");
            break;
        default :
            puts("잘못된 입력!!!!!!");
            break;
    }
}

void searchname(void)
{
    char cliname[15];
    int i, exist=0;

    printf("이름 입력 : ");
    scanf("%s", cliname);

    for(i=0;i<stcount;i++){
        if(strcmp(clients[i]->name, cliname)==0){
            printf("학번 : %10s 이름 : %s\n", clients[i]->stnum, clients[i]->name);
            printf("주소 : %10s 전화번호 : %s\n", clients[i]->address, clients[i]->phonenum);
            exist=1;
            break;
        }
    }

    if(exist==0){
        puts("가입되어있지 않은 학생입니다.");
    }
}

void searchnum(void)
{
    char clinum[15];
    int i, exist=0;

    printf("이름 입력 : ");
    scanf("%s", clinum);

    for(i=0;i<stcount;i++){
        if(strcmp(clients[i]->stnum, clinum)==0){
            printf("학번 : %10s 이름 : %s\n", clients[i]->stnum, clients[i]->name);
            printf("주소 : %10s 전화번호 : %s\n", clients[i]->address, clients[i]->phonenum);
            exist=1;
            break;
        }
    }
    
    if(exist==0){
        puts("가입되어있지 않은 학생입니다.");
    }
}

void searchall(void)
{
    int i;

    puts("--------학생 전체 목록-------");

    for(i=0;i<stcount;i++){
        printf("%d.\n", i);
        printf("학번 : %10s 이름 : %s\n", clients[i]->stnum, clients[i]->name);
        printf("주소 : %10s 전화번호 : %s\n\n", clients[i]->address, clients[i]->phonenum);
    }

    printf("-------------------------------");
}