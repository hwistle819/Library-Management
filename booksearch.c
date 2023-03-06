#include "bpj.h"

extern BOOK** books;
extern int bkcount;

void bksearch(void)
{
    int num;

    puts(">>도서 검색<<\n");
    printf("1. 도서명 검색      2. 출판사명 검색\n");
    printf("3. ISBN 검색        4. 저자명 검색\n");
    printf("5. 전체 검색        6. 나가기\n\n");

    printf("번호를 입력하세요 : ");
    scanf("%d", &num);

    switch(num)
    {
        case 1:
            bksearchname();
            break;
        case 2:
            bksearchpub();
            break;
        case 3:
            bksearchisbn();
            break;
        case 4:
            bksearchaut();
            break;
        case 5 :
            bksearchall();
            break;
        case 6 :
            return ;
        default :
            puts("잘못된 입력");
            return ;
    }
}

void bksearchname(void)
{
    char bkinfo[30];
    int i, cnt=0;
    int impos, pos;
    char stat;

    impos=pos=0;
    
    printf("도서명 입력 : ");
    scanf("%s", bkinfo);

    puts(">>검색 결과<<");

    for(i=0;i<bkcount;i++){
        if(strcmp(books[i]->bkname, bkinfo)==0 && cnt==0){
            printf("도서명 : %s\n", books[i]->bkname);      
            printf("출판사 : %s\n", books[i]->publisher);
            printf("작가 : %s\n", books[i]->author);
            printf("ISBN : %s\n", books[i]->isbn);
            printf("소장처 : %s\n", books[i]->place);
            cnt++;
            break;
        }
    }
    if(cnt==0){//찾는 책이 없을 경우
        puts("\n도서목록에 없습니다.");
        return;
    }
    else{
        for(i=0;i<bkcount;i++){
            if(strcmp(books[i]->bkname, bkinfo)==0){//책 권수만큼 pos++;
                pos++;
                if(books[i]->status=='n'){//대여불가면 impos++;
                    impos++;
                }
            }
        }

        if(pos==impos){
            stat='n';
        }
        else{
            stat='y';
        }
        printf("대여가능 여부 : %c <%d/%d>\n", stat, impos, pos);
    }
}

void bksearchpub(void)
{
    char bkinfo[30];
    char bookname[30];
    int i, j, cnt=0;
    int pos=0;
    char stat;

    strcpy(bookname, "?");
    
    printf("출판사 입력 : ");
    scanf("%s", bkinfo);

    puts(">>검색 결과<<");

    for(i=0;i<bkcount;i++){
        if(strcmp(books[i]->publisher, bkinfo)==0 && strcmp(books[i]->bkname, bookname)!=0 && cnt==0){
            printf("도서명 : %s\n", books[i]->bkname);      
            printf("출판사 : %s\n", books[i]->publisher);
            printf("작가 : %s\n", books[i]->author);
            printf("ISBN : %s\n", books[i]->isbn);
            printf("소장처 : %s\n", books[i]->place);
            for(j=i;j<bkcount;j++){
                if(books[j]->status=='y'){
                    pos++;
                }
            }
            if(pos>0){
                printf("대여가능 여부 : y\n\n");
            }
            else{
                printf("대여가능 여부 : n\n\n");
            }
            cnt++;
        }
    }
    if(cnt==0){//찾는 책이 없을 경우
        puts("\n도서목록에 없습니다.");
        return;
    }
}

void bksearchisbn(void)
{
    char bkinfo[30];
    int i, cnt=0;
    int impos, pos;
    char stat;

    impos=pos=0;
    
    printf("isbn 입력 : ");
    scanf("%s", bkinfo);

    puts(">>검색 결과<<");

    for(i=0;i<bkcount;i++){
        if(strcmp(books[i]->isbn, bkinfo)==0 && cnt==0){
            printf("도서명 : %s\n", books[i]->bkname);      
            printf("출판사 : %s\n", books[i]->publisher);
            printf("작가 : %s\n", books[i]->author);
            printf("ISBN : %s\n", books[i]->isbn);
            printf("소장처 : %s\n", books[i]->place);
            cnt++;
            break;
        }
    }
    if(cnt==0){//찾는 책이 없을 경우
        puts("\n도서목록에 없습니다.");
        return;
    }
    else{
        for(i=0;i<bkcount;i++){
            if(strcmp(books[i]->isbn, bkinfo)==0){//책 권수만큼 pos++;
                pos++;
                if(books[i]->status=='n'){//대여불가면 impos++;
                    impos++;
                }
            }
        }

        if(pos==impos){
            stat='n';
        }
        else{
            stat='y';
        }
        printf("대여가능 여부 : %c <%d/%d>\n", stat, impos, pos);
    }
}

void bksearchaut(void)
{
    char bkinfo[30];
    char bookname[30];
    int i, j, cnt=0;
    int pos=0;
    char stat;

    strcpy(bookname, "?");
    
    printf("저자 입력 : ");
    scanf("%s", bkinfo);

    puts(">>검색 결과<<");

    for(i=0;i<bkcount;i++){
        if(strcmp(books[i]->author, bkinfo)==0 && strcmp(books[i]->bkname, bookname)!=0 && cnt==0){
            printf("도서명 : %s\n", books[i]->bkname);      
            printf("출판사 : %s\n", books[i]->publisher);
            printf("작가 : %s\n", books[i]->author);
            printf("ISBN : %s\n", books[i]->isbn);
            printf("소장처 : %s\n", books[i]->place);
            for(j=i;j<bkcount;j++){
                if(books[j]->status=='y'){
                    pos++;
                }
            }
            if(pos>0){
                printf("대여가능 여부 : y\n\n");
            }
            else{
                printf("대여가능 여부 : n\n\n");
            }
            cnt++;
        }
    }
    if(cnt==0){//찾는 책이 없을 경우
        puts("\n도서목록에 없습니다.");
        return;
    }
}

void bksearchall(void)
{
    char bkinfo[30];
    char bookname[30];
    int i, j, cnt=0;
    int pos=0;
    char stat;

    strcpy(bookname, "?");

    puts("\n>>검색 결과<<\n");

    for(i=0;i<bkcount;i++){
        if(strcmp(books[i]->bkname, bookname)!=0){
            printf("도서명 : %s\n", books[i]->bkname);      
            printf("출판사 : %s\n", books[i]->publisher);
            printf("작가 : %s\n", books[i]->author);
            printf("ISBN : %s\n", books[i]->isbn);
            printf("소장처 : %s\n", books[i]->place);
            for(j=i;j<bkcount;j++){
                if(books[j]->status=='y'){
                    pos++;
                }
            }
            if(pos>0){
                printf("대여가능 여부 : y\n\n");
            }
            else{
                printf("대여가능 여부 : n\n\n");
            }
            strcpy(bookname, books[i]->bkname);
        }
    }
}