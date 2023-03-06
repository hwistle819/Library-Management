#include"bpj.h"

extern CLIENT** clients;
extern int stcount;
extern BORROW** bkbrw;
extern int brcount;

int person(char* idnum, int i)
{
    int status;
    char pass[15];

    printf("PW : ");
    scanf("%s", pass);
    if(strcmp(pass, clients[i]->password)==0){
        status=0;
    }
    else{
        puts("비밀번호가 틀렸습니다.");
        status=1;
    }

    return status;
}

int climenu(int clinum)
{
    int num;
    int retnum=-1;

    puts("\n>>회원메뉴<<");

    while(1){
        puts("\n1. 도서 검색      2. 대여 목록");
        puts("3. 개인정보 수정  4. 회원 탈퇴");
        puts("5. 로그아웃       6. 프로그램 종료");

        printf("번호를 입력하세요 : ");
        scanf("%d", &num);

        switch(num){
            case 1 :
                bksearch();
                break;
            case 2 :
                borrowlist(clinum);
                break;
            case 3 :
                clirevice(clinum);
                break;
            case 4 :
                withdrawal(clinum);
                retnum=0;
                break;
            case 5 :
                puts("\n--로그아웃 되었습니다.--");
                retnum=0;
                break;
            case 6 :
                retnum=3;
                puts("프로그램을 종료합니다.");
                break;
        }
        if(retnum==0 | retnum==3){
            break;
        }
    }
    return retnum;
}

int admenu(void){
    int num;
    int retnum;

    puts(">>관리자 메뉴<<");
    
    while(1){
        puts("\n1. 도서 등록  2. 도서 삭제");
        puts("3. 도서 대여  4. 도서 반납");
        puts("5. 도서 검색  6. 회원 목록");
        puts("7. 로그 아웃  8. 프로그램 종료\n");

        printf("번호를 입력하세요 : ");
        scanf("%d", &num);

        switch(num){
            case 1:
                bookwrt();
                break;
            case 2:
                bkdelete();
                break;
            case 3:
                borrow();
                break;
            case 4:
                bkreturn();
                break;
            case 5:
                bksearch();
                break;
            case 6:
                clientlist();
                break;
            case 7:
                retnum=1;
                puts("로그아웃");
                break;
            case 8:
                retnum=3;
                puts("프로그램을 종료합니다.");
                break;
        }
        if(retnum==1 | retnum==3){
            break;
        }
    }

    return retnum;
}

void borrowlist(int clinum)
{
    int i;

    puts(">>회원의 대여 목록<<\n");
    
    for(i=0;i<brcount;i++){
        if(strcmp(clients[clinum]->stnum, bkbrw[i]->stnum)==0){
            printf("도서번호 : %8d", bkbrw[i]->bknum);
            printf("도서명 : %s\n", bkbrw[i]->bkname);
            printf("대여일 : %d년%d월%d일%d:%d:%d\n", bkbrw[i]->tm_year, \
            bkbrw[i]->tm_mon, bkbrw[i]->tm_mday, bkbrw[i]->tm_hour, \
            bkbrw[i]->tm_min, bkbrw[i]->tm_sec);

            if(bkbrw[i]->bkreturn=='n'){
                puts("미반닙\n");
            }
            else{
                printf("대여일 : %d년%d월%d일%d:%d:%d\n", bkbrw[i]->rettm_year, \
                bkbrw[i]->rettm_mon, bkbrw[i]->rettm_mday, bkbrw[i]->rettm_hour, \
                bkbrw[i]->rettm_min, bkbrw[i]->rettm_sec);
            }
        }
    }
}