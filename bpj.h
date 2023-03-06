#ifndef _bpj_h
#define _bpj_h
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define ADPASS "1q2w3e4r"

typedef struct client{
	char stnum[10];
	char password[20];
	char name[15];
	char address[80];
	char phonenum[20];
}CLIENT;

typedef struct book{
	int bknum;
	char bkname[30];
	char publisher[30];
	char author[20];
	char isbn[15];
	char place[25];
	char status;
}BOOK;

typedef struct borrow{
	char stnum[10];
	int bknum;
	char bkname[30];
	int tm_year;        /* 1900년 부터의 년                */
	int tm_mon;         /* 월, range 0 to 11             */
	int tm_mday;        /* 일, range 1 to 31             */
	int tm_wday;        /* 요일, range 일(0) to 토(6)      */
	int tm_hour;        /* 시간, range 0 to 23            */
	int tm_min;         /* 분, range 0 to 59             */
	int tm_sec;         /* 초,  range 0 to 59            */
	int rettm_year;
	int rettm_mon;
	int rettm_mday;
	int rettm_wday;
	int rettm_hour;
	int rettm_min;
	int rettm_sec;
	char bkreturn;	//반납여부
}BORROW;

typedef struct bookret{
	
}BOOKRET;

CLIENT *signin(void);//
void copen(void);//
CLIENT* copen_1(FILE **);//
int idcomp(void);//
int person(char*, int);//
int admenu(void);//
int climenu(int);//
void cliwrt(CLIENT*);//
void clirevice(int);//
void withdrawal(int);//
void clientlist(void);//
void searchname(void);//
void searchnum(void);//
void searchall(void);//
void bopen(void);//
BOOK* bopen_1(FILE**);//
void bookwrt(void);//
BOOK* bkregister(void);//
void ropen(void);//
BORROW* ropen_1(FILE**);//
void borrow(void);//
void borrow_1(int);//
void brwwrt(BORROW*);//
void bkreturn(void);//
void bkdelete(void);//
void bkdelete_1(void);//
void bkdelete_2(void);//
void bksearch(void);//
void bksearchname(void);//
void bksearchpub(void);//
void bksearchisbn(void);//
void bksearchaut(void);//
void bksearchall(void);//
void borrowlist(int);//

#endif