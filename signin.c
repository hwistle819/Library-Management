#include"bpj.h"

extern CLIENT** clients;
extern BOOK** books;
extern int stcount;
extern int bkcount;

CLIENT* signin(void)
{
    CLIENT* stinfo;
    
    int i=0;

    stinfo=(CLIENT*)malloc(sizeof(CLIENT));
    
    puts(">>회원가입<<");
    puts("인적사항을 입력하세요.");

    if(stcount!=0){
        while(1){
            
            printf("학번 : ");
            scanf("%s", stinfo->stnum);

            for(i=0 ; i < stcount ; i++){
                if(strcmp(stinfo->stnum, clients[i]->stnum)==0){
                    strcpy(stinfo->stnum, "0");
                    break;
                }
            }
            if(strcmp(stinfo->stnum, "0")==0){
                puts("이미 동일한 학번으로 가입되어있습니다. 다시 입력하세요");
            }
            else{
                break;
            }
        }
    }
    else{
        printf("학번 : ");
        scanf("%s", stinfo->stnum);
    }
    
    printf("비밀번호 : ");
    scanf("%s", stinfo->password);
    printf("이름 : ");
    scanf("%s", stinfo->name);
    printf("주소 : ");
    scanf("%s", stinfo->address);
    printf("전화번호 : ");
    scanf("%s", stinfo->phonenum);
    
    return stinfo;
}

BOOK* bkregister(void)
{
    BOOK* bkinfo;
    int i, j;

    bkinfo=(BOOK*)malloc(sizeof(BOOK));

    puts(">>도서 등록<<");

    printf("도서명 : ");
    scanf("%s", bkinfo->bkname);
    printf("출판사 : ");
    scanf("%s", bkinfo->publisher);
    printf("저자명 : ");
    scanf("%s", bkinfo->author);
    printf("ISBN : ");
    scanf("%s", bkinfo->isbn);
    printf("소장처");
    scanf("%s", bkinfo->place);
    bkinfo->status='y';

    return bkinfo;
}