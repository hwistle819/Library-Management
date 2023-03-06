#include "bpj.h"

extern BOOK** books;
extern int bkcount;

void bookwrt(void)
{
    BOOK* bookinfo;
    BOOK* temp;
    FILE* fp;
    int i, j;
    char c;
    
    bookinfo=bkregister();

    books=(BOOK**)realloc(books, sizeof(BOOK*)*(bkcount+1));
    books[bkcount]=bookinfo;
    bkcount++;

    for(i=0;i<bkcount;i++){//책 이름순으로 정렬
        for(j=i;j<bkcount;j++){
            if(strcmp(books[i]->bkname, books[j]->bkname)>0){
                temp=books[i];
                books[i]=books[j];
                books[j]=temp;
            }
        }
    }

    for(i=0;i<bkcount;i++){//모든 과정 후 일련번호 지급
        books[i]->bknum=i;
    }

    fp=fopen("book.txt", "w");
    
    for(i=0;i<bkcount;i++){
        fprintf(fp, "%8d | %-16s | %-16s | %-16s | %-16s | %-16s | %c\n",\
        books[i]->bknum, books[i]->bkname, books[i]->publisher, \
        books[i]-> author, books[i]->isbn, books[i]-> place, \
        books[i]->status);
    }
}

void bkdelete(void)
{
    int num;

    puts(">>도서 삭제<<");
    puts("\n1. 도서명 검색  2.ISBN 검색");
    printf("번호를 입력하세요 : ");
    scanf("%d", &num);

    switch(num){
        case 1 :
            bkdelete_1();
            break;
        case 2 :
            bkdelete_2();
            break;
        default :
            puts("잘못된 입력");
            break;
    }
}

void bkdelete_1(void)
{
    int i, start, cnt=0;
    int delnum;
    char bookname[20];
    FILE* fp;

    printf("도서명 입력 : ");
    scanf("%s", bookname);

    for(i=0;i<bkcount;i++){
        if(strcmp(books[i]->bkname, bookname)==0 && cnt==0){
            start=i;
            cnt++;
        }

        if(cnt>0){
            if(strcmp(books[i]->bkname, bookname)!=0){
                break;
            }
            cnt++;
        }
    }
    printf("--%d-n", start);
    for(i=start;i<start+cnt-1;i++){
        printf("\nbooknum : %d    ", books[i]->bknum);
        printf("bookname : %s\n ", books[i]->bkname);
        printf("publisher : %s  ", books[i]->publisher);
        printf("author : %s\n   ", books[i]->author);
        printf("ISBN : %s       ", books[i]->isbn);
        printf("space : %s\n    ", books[i]->place);
        printf("삭제 가능 여부 : %c\n", books[i]->status);
    }

    printf("도서번호 입력 : ");
    scanf("%d", &delnum);

    if(books[delnum]->status!='n'){//반납가능여부가 n일 때 예외처리 할 것
        puts("아직 반납되지 않은 책입니다.");
        puts("도서삭제 불가");
        return;
    }

    bkcount--;

    for(i=start;i<bkcount;i++){
        books[i]=books[i+1];
        books[i]->bknum=i;
    }

    books=(BOOK**)realloc(books, sizeof(BOOK*)*(bkcount));

    fp=fopen("book.txt", "w");

    for(i=0;i<bkcount;i++){
        fprintf(fp, "%8d | %-16s | %-16s | %-16s | %-16s | %-16s | %c\n",\
        books[i]->bknum, books[i]->bkname, books[i]->publisher, \
        books[i]-> author, books[i]->isbn, books[i]-> place, \
        books[i]->status);
    }

    puts("도서 삭제 완료");
}

void bkdelete_2(void)
{
    int i, start, cnt=0;
    char delnum;
    char isbn[20];
    FILE* fp;

    printf("ISBN 입력 : ");
    scanf("%s", isbn);

    for(i=0;i<bkcount;i++){
        if(strcmp(books[i]->isbn, isbn)==0 && cnt==0){
            start=i;
            cnt++;
        }

        if(cnt>0){
            if(strcmp(books[i]->isbn, isbn)!=0){
                break;
            }
            cnt++;
        }
    }
    printf("--%d-n", start);
    for(i=start;i<start+cnt-1;i++){
        printf("\nbooknum : %d    ", books[i]->bknum);
        printf("bookname : %s\n ", books[i]->bkname);
        printf("publisher : %s  ", books[i]->publisher);
        printf("author : %s\n   ", books[i]->author);
        printf("ISBN : %s       ", books[i]->isbn);
        printf("space : %s\n    ", books[i]->place);
        printf("삭제 가능 여부 : %c\n", books[i]->status);
    }

    printf("도서번호 입력 : ");
    scanf("%d", &delnum);

    if(books[delnum]->status!='n'){//반납가능여부가 n일 때 예외처리 할 것
        puts("아직 반납되지 않은 책입니다.");
        puts("도서삭제 불가");
        return;
    }

    bkcount--;

    for(i=start;i<bkcount;i++){
        books[i]=books[i+1];
        books[i]->bknum=i;
    }

    books=(BOOK**)realloc(books, sizeof(BOOK*)*(bkcount));

    fp=fopen("book.txt", "w");

    for(i=0;i<bkcount;i++){
        fprintf(fp, "%8d | %-16s | %-16s | %-16s | %-16s | %-16s | %c\n",\
        books[i]->bknum, books[i]->bkname, books[i]->publisher, \
        books[i]-> author, books[i]->isbn, books[i]-> place, \
        books[i]->status);
    }

    puts("도서 삭제 완료");
}