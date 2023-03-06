#include "bpj.h"

extern CLIENT** clients;
extern int stcount;

int idcomp(void)
{
    int clistatus;//status는 일반사용자 상태확인용
    int num, i, confirm;
    char idnum[10];//로그인 ID
    char pass[15];//로그인 비밀번호

    printf("ID : ");
    scanf("%s", idnum);
    if(strcmp(idnum, "admin")==0){//ID가 어드민이면
        printf("PW : ");
        scanf("%s", pass);
        if(strcmp(pass, ADPASS)==0){
            num=admenu();
        }
        else{
            puts("비밀번호가 틀렸습니다.");
        }
        
        
    }
    else{
        clistatus=3;
        for(i=0;i<stcount;i++){
            if(strcmp(idnum, clients[i]->stnum)==0){
                clistatus=person(idnum, i);
                if(clistatus==0){
                    num=climenu(i);
                }
                break;
            }
        }

        if(clistatus==3){
            puts("가입되어있지 않은 사용자입니다.\n");
        }
    }
    

    /*
        리턴값에 따라
                비밀번호 오입력 = 2;
                프로그램 종료 = 3;

                회원탈퇴 = 5;
                회원정보 변경됨을 알리는 출력 = 9;
    */
   return num;
}