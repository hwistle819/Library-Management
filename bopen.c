#include "bpj.h"

extern BOOK** books;
extern int bkcount;

void bopen(void)
{
    FILE* fp;
    int i;
    BOOK* tempo;

    fp=fopen("book.txt", "r");

    if(fp==NULL){
        fp=fopen("book.txt", "w");
        fclose(fp);
        return;
    }

    while(1){
        tempo=bopen_1(&fp);

        if(tempo->bknum==-1){
            break;
        }

        if(bkcount==0){
            books[0]=(BOOK*)malloc(sizeof(BOOK));
        }
        else{
            books=(BOOK**)realloc(books, sizeof(BOOK*)*(bkcount+1));
        }

        books[bkcount] = tempo;
        bkcount++;
    }
    fclose(fp);
}

BOOK* bopen_1(FILE** fp)
{
    BOOK* temp;
    int res;
    char c;

    temp=(BOOK*)malloc(sizeof(BOOK));

    res = fscanf(*fp, "%d %c %s %c %s %c %s %c %s %c %s %c %c", &temp->bknum, \
    &c, temp->bkname, &c, temp->publisher, &c, temp-> author, &c, temp->isbn, \
    &c, temp-> place, &c, &temp->status);

    if(res==EOF){
        temp->bknum=-1;
    }

    return temp;
}