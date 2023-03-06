#include"bpj.h"

extern BORROW** bkbrw;
extern int brcount;
extern BOOK** books;
extern int bkcount;
extern CLIENT** clients;
extern int stcount;

void cliwrt(CLIENT* stinfo)
{
    FILE* ofp;
    CLIENT* temp;
    int i, j;

    clients=(CLIENT**)realloc(clients, sizeof(CLIENT*)*(stcount+1));
    clients[stcount]=stinfo;
    stcount++;
    
    for(i=0;i<stcount;i++){
        for(j=i;j<stcount;j++){
            if(strcmp(clients[i]->stnum, clients[j]->stnum)>0){
                temp=clients[i];
                clients[i]=clients[j];
                clients[j]=temp;
            }
        }
    }

    ofp = fopen("client.txt", "w");

    for(i=0;i<stcount;i++){
        fprintf(ofp, "%s | %s | %s | %s | %s\n", clients[i]->stnum, \
        clients[i]->password, clients[i]->name, clients[i]->address, \
        clients[i]->phonenum);
    }
    
}

void clirevice(int clinum)
{
    FILE* fp;
    int i;

    puts("---현재 당신의 정보---");
    printf("학번 : %-11s password : %s\n", clients[clinum]->stnum, clients[clinum]->password);
    printf("이름 : %-11s 주소 : %s\n", clients[clinum]->name, clients[clinum]->address);
    printf("전화번호 : %s\n\n", clients[clinum]->phonenum);

    puts("---정보 수정 입력---");
    printf("비밀번호 : ");
    scanf("%s", clients[clinum]->password);
    printf("주소 : ");
    scanf("%s", clients[clinum]->address);
    printf("전화번호 : ");
    scanf("%s", clients[clinum]->phonenum);
    
    fp=fopen("client.txt", "w");

    for(i=0;i<stcount;i++){
        fprintf(fp, "%s | %s | %s | %s | %s\n", clients[i]->stnum, \
        clients[i]->password, clients[i]->name, clients[i]->address, \
        clients[i]->phonenum);
    }

    puts("회원정보가 변경되었습니다.");
}

void withdrawal(int clinum){
    int i;
    FILE* fp;

    //나중에 도서반납 여부 확인하는 부분 추가할 것
    for(i=0;i<brcount;i++){
        if(strcmp(clients[clinum]->stnum, bkbrw[i]->stnum)==0){
            if(bkbrw[i]->bkreturn=='n'){
                puts("반납하지 않은 책이 있습니다.");
                puts("회원탈퇴 불가");
                return;
            }
        }
    }
    stcount--;

    for(i=clinum;i<stcount;i++){
        clients[i]=clients[i+1];
    }
    
    
    clients=(CLIENT**)realloc(clients, sizeof(CLIENT*)*(stcount));

    fp=fopen("client.txt", "w");

    for(i=0;i<stcount;i++){
        fprintf(fp, "%s | %s | %s | %s | %s\n", clients[i]->stnum, \
        clients[i]->password, clients[i]->name, clients[i]->address, \
        clients[i]->phonenum);
    }
    puts("회원탈퇴가 완료되었습니다.\n");
}