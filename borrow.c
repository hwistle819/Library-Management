#include"bpj.h"

extern BORROW** bkbrw;
extern int brcount;
extern BOOK** books;
extern int bkcount;
extern CLIENT** clients;
extern int stcount;

void borrow(void)
{
    int num;

    puts(">>도서 대여<<");
    puts("\n1. 도서명 검색      2. ISBN 검색");
    printf("번호를 입력하세요 : ");
    scanf("%d", &num);

    switch(num){
        case 1 :
        case 2 :
            borrow_1(num);
            break;
        default :
            puts("잘못된 입력");
            break;
    }
}

void borrow_1(int num)
{
    int i, start, cnt=0;
    int cliexist=0;
    int bknum;
    char stnum[20];
    char bkinfo[20];
    BORROW* brwinfo;
    FILE* bfp;

    brwinfo=(BORROW*)malloc(sizeof(BORROW));

    if(num==1){
        printf("도서명 입력 : ");
        scanf("%s", bkinfo);

        for(i=0;i<bkcount;i++){
            if(strcmp(books[i]->bkname, bkinfo)==0 && cnt==0){
                start=i;
                cnt++;
            }

            if(cnt>0){
                if(strcmp(books[i]->bkname, bkinfo)!=0){
                    break;
                }
                cnt++;
            }
        }
        if(cnt==0){//찾는 책이 없을 경우
            puts("\n도서목록에 없습니다.");
            return;
        }
    }
    else{
        printf("ISBN 입력 : ");
        scanf("%s", bkinfo);

        for(i=0;i<bkcount;i++){
            if(strcmp(books[i]->isbn, bkinfo)==0 && cnt==0){
                start=i;
                cnt++;
            }

            if(cnt>0){
                if(strcmp(books[i]->isbn, bkinfo)!=0){
                    break;
                }
                cnt++;
            }
        }
        if(cnt==0){//찾는 책이 없을 경우
            puts("\n도서목록에 없습니다.");
            return;
        }
    }

    puts(">>대여 가능 도서<<");
    for(i=start;i<start+cnt-1;i++){
        printf("\n도서번호 : %d   ", books[i]->bknum);
        printf("도서명 : %s\n", books[i]->bkname);
        printf("출판사 : %s     ", books[i]->publisher);
        printf("저자 : %s\n", books[i]->author);
        printf("ISBN : %s       ", books[i]->isbn);
        printf("소장처 : %s\n", books[i]->place);
        printf("대여 가능 여부 : %c\n", books[i]->status);
    }

    strcpy(brwinfo->bkname, books[i-1]->bkname);
    //마지막 for문에서 i가 증가되어 그대로 하면 쓰레기값이 들어가기에 -1함

    printf("학번 입력 : ");
    scanf("%s", brwinfo->stnum);/////
    
    for(i=0;i<stcount;i++){//입력한 회원번호 존재여부 확인
        if(strcmp(clients[i]->stnum, brwinfo->stnum)==0){
            cliexist=1;
        }
    }
    if(cliexist!=1){
        puts("없는 회원입니다.");
        return;
    }

    printf("도서번호 입력 : ");
    scanf("%d", &brwinfo->bknum);

    if(books[brwinfo->bknum]->status=='n' || books[brwinfo->bknum]->status=='N'){
        puts("대여 불가능한 책입니다.");
        return;
    }
    else{
        bfp=fopen("book.txt", "w");

        books[brwinfo->bknum]->status='n';//책목록 파일에 대여불가처리
        for(i=0;i<bkcount;i++){
            fprintf(bfp, "%8d | %-16s | %-16s | %-16s | %-16s | %-16s | %c\n",\
            books[i]->bknum, books[i]->bkname, books[i]->publisher, \
            books[i]-> author, books[i]->isbn, books[i]-> place, \
            books[i]->status);
        }

        fclose(bfp);
        brwwrt(brwinfo);
    }

    return;
}

void brwwrt(BORROW* brwinfo)
{
    struct tm *t;
    time_t timer;
    FILE* fp;
    int i, j;

    timer = time(NULL);
    t = localtime(&timer);

    brwinfo->tm_year = t->tm_year + 1900;
    brwinfo->tm_mon = t->tm_mon + 1;
    brwinfo->tm_mday = t->tm_mday;
    brwinfo->tm_hour = t->tm_hour;
    brwinfo->tm_min = t->tm_min;
    brwinfo->tm_sec = t->tm_sec;
    brwinfo->tm_wday = t->tm_wday;
    brwinfo->bkreturn = 'n';
    brwinfo->rettm_year = brwinfo->rettm_mon = brwinfo->rettm_mday = brwinfo->rettm_wday \
    = brwinfo->rettm_hour = brwinfo-> rettm_min = brwinfo->rettm_sec= 0;

    bkbrw=(BORROW**)realloc(bkbrw, sizeof(BORROW*)*(brcount+1));
    bkbrw[brcount]=brwinfo;
    brcount++;

    fp=fopen("borrow.txt", "w");

    for(i=0;i<brcount;i++){
        fprintf(fp, "%s | %d | %s | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %c\n", \
        bkbrw[i]->stnum, bkbrw[i]->bknum, bkbrw[i]->bkname, bkbrw[i]->tm_year, \
        bkbrw[i]->tm_mon, bkbrw[i]->tm_mday, bkbrw[i]->tm_wday, bkbrw[i]->tm_hour, \
        bkbrw[i]->tm_min, bkbrw[i]->tm_sec, bkbrw[i]->rettm_year, bkbrw[i]->rettm_mon, \
        bkbrw[i]->rettm_mday, bkbrw[i]->rettm_wday, bkbrw[i]->rettm_hour, bkbrw[i]->rettm_min, \
        bkbrw[i]->rettm_sec, bkbrw[i]->bkreturn);
    }
}

void bkreturn(void)
{
    struct tm *t;
    time_t timer;
    FILE* fp;
    FILE* bfp;
    int i;
    int retnum;
    char retstnum[10];

    timer = time(NULL);
    t = localtime(&timer);

    puts(">>도서 반납<<\n");
    printf("학번을 입력하세요 : ");
    scanf("%s", retstnum);
    puts("\n>>회원의 대여 목록<<\n");

    for(i=0;i<brcount;i++){
        if(strcmp(bkbrw[i]->stnum, retstnum)==0 && bkbrw[i]->bkreturn == 'n'){
            printf("도서번호 : %d   ", bkbrw[i]->bknum);
            printf("도서명 : %s\n", bkbrw[i]->bkname);
            printf("대여일 %d년 %d월 %d일 %d:%d:%d\n", bkbrw[i]->tm_year, \
            bkbrw[i]->tm_mon, bkbrw[i]->tm_mday, bkbrw[i]->tm_hour, \
            bkbrw[i]->tm_min, bkbrw[i]->tm_sec);
        }
        printf("\n");
    }

    printf("반납할 도서번호를 입력하세요 : ");
    scanf("%d", &retnum);

    bfp=fopen("book.txt", "w");
    books[retnum]->status='y';//book.txt파일에 해당 책 대여가능처리
    for(i=0;i<bkcount;i++){
        fprintf(bfp, "%8d | %-16s | %-16s | %-16s | %-16s | %-16s | %c\n",\
        books[i]->bknum, books[i]->bkname, books[i]->publisher, \
        books[i]-> author, books[i]->isbn, books[i]-> place, \
        books[i]->status);
    }

    fclose(bfp);
    
    for(i=0;i<brcount;i++){
        if(bkbrw[i]->bknum==retnum && bkbrw[i]->bkreturn=='n'){
            bkbrw[i]->bkreturn='y';
            bkbrw[i]->rettm_year = t->tm_year + 1900;
            bkbrw[i]->rettm_mon = t->tm_mon + 1;
            bkbrw[i]->rettm_mday = t->tm_mday;
            bkbrw[i]->rettm_hour = t->tm_hour;
            bkbrw[i]->rettm_min = t->tm_min;
            bkbrw[i]->rettm_sec = t->tm_sec;
            bkbrw[i]->rettm_wday = t->tm_wday;
            break;
        }
    }

    

    fp=fopen("borrow.txt", "w");

    for(i=0;i<brcount;i++){
        fprintf(fp, "%s | %d | %s | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %c\n", \
        bkbrw[i]->stnum, bkbrw[i]->bknum, bkbrw[i]->bkname, bkbrw[i]->tm_year, \
        bkbrw[i]->tm_mon, bkbrw[i]->tm_mday, bkbrw[i]->tm_wday, bkbrw[i]->tm_hour, \
        bkbrw[i]->tm_min, bkbrw[i]->tm_sec, bkbrw[i]->rettm_year, bkbrw[i]->rettm_mon, \
        bkbrw[i]->rettm_mday, bkbrw[i]->rettm_wday, bkbrw[i]->rettm_hour, bkbrw[i]->rettm_min, \
        bkbrw[i]->rettm_sec, bkbrw[i]->bkreturn);
    }
    fclose(fp);
}