#include"bpj.h"

extern BORROW** bkbrw;
extern int brcount;

void ropen(void)
{
    FILE* fp;
    int i;
    BORROW* tempo;

    fp=fopen("borrow.txt", "r");

    if(fp==NULL){
        fp=fopen("borrow.txt", "w");
        fclose(fp);
        return;
    }
    while(1){
        tempo=ropen_1(&fp);

        if(strcmp(tempo->stnum, "0")==0){
            break;
        }

        if(brcount==0){
            bkbrw[0]=(BORROW*)malloc(sizeof(BORROW));
        }
        else{
            bkbrw=(BORROW**)realloc(bkbrw, sizeof(BORROW*)*(brcount+1));
        }

        bkbrw[brcount] = tempo;
        brcount++;
    }
    fclose(fp);
}

BORROW* ropen_1(FILE** fp)
{
    BORROW* temp;
    int res;
    char c;

    temp=(BORROW*)malloc(sizeof(BORROW));

    res=fscanf(*fp, "%s %c %d %c %s %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %c", \
    temp->stnum, &c, &temp->bknum, &c, temp->bkname, &c, &temp->tm_year, &c, &temp->tm_mon, \
    &c, &temp->tm_mday, &c, &temp->tm_wday, &c, &temp->tm_hour, &c, &temp->tm_min, &c, &temp->tm_sec, &c, \
    &temp->rettm_year, &c, &temp->rettm_mon, &c, &temp->rettm_mday, &c, &temp->rettm_wday, \
    &c, &temp->rettm_hour, &c, &temp->rettm_min, &c, &temp->rettm_sec, &c, &temp->bkreturn);
    
    if(res==EOF){
        strcpy(temp->stnum, "0");
    }

    return temp;
}