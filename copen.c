#include"bpj.h"

extern CLIENT** clients;
extern int stcount;

void copen(void)
{    
    FILE* fp;
    int i;
    CLIENT* tempo;

    fp=fopen("client.txt", "r");

    if(fp==NULL){
        fp=fopen("client.txt", "w");
        fclose(fp);
        return;
    }
    
    while(1){
        tempo=copen_1(&fp);

        if(strcmp(tempo->stnum, "0")==0){       
            break;
        }

        if(stcount==0){
            clients[0]=(CLIENT*)malloc(sizeof(CLIENT));
        }
        else{
            clients=(CLIENT**)realloc(clients, sizeof(CLIENT*)*(stcount+1));
        }

        clients[stcount] = tempo;
        stcount++;
    }
    fclose(fp);
}

CLIENT* copen_1(FILE** fp)
{
    CLIENT* temp;
    int res;
    char c;

    temp=(CLIENT*)malloc(sizeof(CLIENT));

    res = fscanf(*fp, "%s %c %s %c %s %c %s %c %s", temp->stnum, &c, \
    temp->password, &c, temp->name, &c, temp->address, &c, temp->phonenum);//txt파일에서 불러와 구조체에 담음

    if(res==EOF){
        strcpy(temp->stnum, "0");
    }

    return temp;
}