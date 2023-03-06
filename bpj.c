#include"bpj.h"

BOOK** books;
int bkcount=0;
CLIENT** clients;//파일에서 정보 불러와 담을 전역변수
int stcount=0;//그러면서 동시에 학생 수를 셀 변수
BORROW** bkbrw;
int brcount=0;

int main(void)
{
    CLIENT* cli;
    int num, i;
    
    books=(BOOK**)malloc(sizeof(BOOK*));
    cli=(CLIENT*)malloc(sizeof(CLIENT));
    clients=(CLIENT**)malloc(sizeof(CLIENT*));//전역변수의 최초 할당은 메인에서 해야함.
    bkbrw=(BORROW**)malloc(sizeof(BORROW*));

    copen(); 
    bopen();
    ropen();
    /*
    for(i=0;i<stcount;i++){
        printf("%s %s %s %s %s\n", clients[i]->stnum, clients[i]->password, clients[i]->name, clients[i]->address, clients[i]->phonenum);
    }*/
    puts(">>도서관 서비스<<");

    while(1){
        puts("\n1. 회원가입   2.로그인    3.프로그램 종료");
        printf("번호를 선택하세요 : ");
        scanf("%d", &num);

        switch(num){
            case 1 :
                cli=signin();
                cliwrt(cli);
                break;
            case 2 :
                puts("\n>>로그인<<\n");
                num=idcomp();
                //회원메뉴에서 프로그램 종료시 3을 리턴받아 메인에서 종료
                break;
            case 3 :
                puts("프로그램을 종료합니다.");
                break;
            default :
                puts("오입력입니다. 다시 입력하세요.");
                break;
        }

        if(num==3){
            break;
        }
    }


    return 0;
}