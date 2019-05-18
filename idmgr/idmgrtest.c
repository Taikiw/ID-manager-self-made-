#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#define MAXCNT 100
// #define CK printf("===%d===",__LINE__);
typedef struct Manager{
  char Name[30];
  char AccountID[100];
  char MailAdress1[100];
  char MailAdress2[100];
  char PassWord[100];
  struct Manager *nextmgr;
}Mgr;

int IDMGR(void);
int Startmenu(void);
Mgr *LoadingFile(Mgr *);
int Registration(Mgr *,Mgr *);
int Swinput(Mgr *,Mgr *,int);
int Check(Mgr *,char *);
Mgr *Checkup(Mgr *,char *);
int Updater(Mgr *,char *);
int Fileoutput(Mgr *);
int DisplayList(Mgr *); //Display Password List
int PwG(void); //Password Generator
int Select(int); //Checking select answer
int Updateyn(void); //Checking update

int main(void){
  int selectmain,mode=0;
  printf("Which one do you want to start ?\n");
  printf("ID MANAGER :0 Password Generator :1 >");
  selectmain = Select(mode);
  switch(selectmain){
    case 0:
      IDMGR(void);
      break;
    case 1:
      PwG(void);
      break;
    default:
      return -1;
  }
  return 0;
}

int IDMGR(){
  int selectmenu,mode=1;
  selectmenu = Startmenu(mode);
  Mgr *mgrp;
  Mgr *nextstartp;
  mgrp = (Mgr *)malloc(sizeof(Mgr));
  nextstartp = LoadingFile(mgrp);
  switch(selectmenu){
    case 0:
      Regstration(mgrp,nextstartp);
    case 1:
      if(mgrp == nextstartp){
        printf("\tCannot Continue.\n");
        return -1;
      }
      DisplayList(mgrp);
      break;
    case 2:
      printf("END\n");
    default:
      return -1;
  }
  return 0;
}

int Startmenu(){
  int mode=1;
  system("cls");
  printf("\n");
  printf("                ----------------------------------------------------\n");
  printf("                          ----- ID MANAGER START MENU ----          \n");
  printf("                ----------------------------------------------------\n");
  printf("\tRegistration or Change management :0 Display Password List :1 END :2 >");
  return Select(mode);
}

Mgr *LoadingFile(Mgr *lmgrp){
  int afsearch,load; //afserch : available flie search
  Mgr *nextlmgrp;
  Mgr *retmgrp; //ret : return
  FILE *lfp; //Loading file pointer
  afsearch =
  if(afsearch == 1){
    if((lfp=fopen("ID_data.txt","w"))==NULL){
      printf("\tCannot Open\n");
      exit(0);
    }
    printf("\tCreated new file ID_data.txt\n");
    fclose(lfp);
  }else if(afsearch == 0){
    printf("\tData Loading...\n");
  }
  if((lfp=fopen("ID_data.txt","r"))==NULL){
    printf("\tCannot Open\n");
    exit(0);
  }
  for(load=0;load<MAXCNT;load++){
    lmgrp->nextmgr = (Mgr*)malloc(sizeof(Mgr));
    nextlmgrp = lmgrp->nextmgr;
    nextlmgrp->nextmgr = NULL;
    if(fscanf(lfp,"%[^,],%[^,],%[^,],%[^,],%s\n",lmgrp->Name,lmgrp->AccountID,lmgrp->MailAdress1,lmgrp->MailAdress2,lmgrp->PassWord)==EOF){
      free(lmgrp->nextmgr);
      lmgrp->nextmgr = NULL;
      fclose(lfp);
      printf("\tFinish Loading\n");
      return lmgrp;
    }
    lmgrp = lmgrp->nextmgr;
  }
  fclose(lfp);
  printf("\tFinish Loading\n");
  retmgrp = lmgrp->nextmgr;
  return retmgrp;
}

int Registration(Mgr *startmgrp,Mgr *rmgrp){
  int reg,inp; //reg : Register
  FILE *rfp; //Register file pointer
  printf("      \tDATA REGISTER\n");
  printf("     \t** ATTENTION **\n");
  printf("\tIf there is nothing to enter , please enter 'no'\n");
  for(reg=0;reg<numor;reg++){
    for(inp=0;inp<5;inp++){
      Swinput(rmgrp,inp);
      printf("\n");
    }
    if(reg == numor-1){
      rmgrp->nextmgr = NULL;
      break;
    }
    rmgrp->nextmgr = (Mgr *)malloc(sizeof(Mgr));
    rmgrp = rmgrp->nextmgr;
  }
  printf("\tRegistration Complete\n");
  Fileoutput(startmgrp);
  return 0;
}

int Swinput(Mgr *swmgrp,int swinp){
  switch(swinp){
    case 0:
      printf("-------------------------------------------------------------\n");
      printf("\tSite Name >");
      scanf(" %s",swmgrp->Name);
      break;
    case 1:
      printf("\tAccount ID >");
      scanf(" %s",swmgrp->AccountID);
      break;
    case 2:
      printf("\tMail Adress1 >");
      scanf(" %s",swmgrp->MailAdress1);
      break;
    case 3:
      printf("\tMail Adress2 >");
      scanf(" %s",swmgrp->MailAdress2);
      break;
    case 4:
      printf("\tPass Word >");
      scanf(" %s",swmgrp->PassWord);
      printf("-------------------------------------------------------------\n");
      break;
    default:
      return -1;
  }
  return 0;
}

int Check(){

}

int Fileoutput(Mgr *fomgrp){
  Mgr *nextfomgrp;
  FILE *cpyfp;
  if((cpyfp=fopen("newdata.txt","w")) == NULL){
    printf("\tCannot Open\n");
    return -1;
  }
  while(1){
    fprintf(cpyfp,"%s,",fomgrp->Name);
    fprintf(cpyfp,"%s,",fomgrp->AccountID);
    fprintf(cpyfp,"%s,",fomgrp->MailAdress1);
    fprintf(cpyfp,"%s,",fomgrp->MailAdress2);
    fprintf(cpyfp,"%s\n",fomgrp->PassWord);
    if(fomgrp->nextmgr != NULL){
      nextfomgrp = fomgrp->nextmgr;
      free(fomgrp);
      fomgrp = nextfomgrp;
    }else{
      free(fomgrp);
      break;
    }
  }
  fclose(cpyfp);
  system("copy /B newdata.txt ID_data.txt");
  if(DeleteFile("newdata.txt")){
    printf("\tStorage Complete.\n");
  }else{
    printf("\tCannot File Delete.\n");
    exit(0);
  }
  return 0;
}

int Select(int mode){
  int select;
  char selectyn;
  switch(mode){
    case 0:
      scanf("%d",&selct);
      while(select < 0 || 1 < select){
        printf("\tRe: ID MANAGER :0 Password Generator :1 >");
        scanf(" %d",&select);
      }
      break;
    case 1:
      scanf(" %d",&select);
      while(select < 0 || 2 < select){
        printf("\tRe: Registration or Change management:0 Display Password List :1 END :2 >");
        scanf(" %d",&select);
      }
      break;
    case 2:
      scanf(" %c",&selectyn);
      while((selectyn != 'y') && (selectyn != 'n')){
        printf("\tRe: Yes : y or No : n >");
        scanf(" %c",&selectyn);
      }
      if(selectyn =='y'){
        return 1;
      }
      if(selectyn =='n'){
        return 0;
      }
      return 1;
    default:
      return -1;
}

int PwG(void){
	int ynans,numoc,c,r,mode=2; //numoc : Number of characters
	char *pw;
	printf("\tIncluding upper case letter ? Yes : y or No : n >");
  ynans = Select(mode);
	printf("\tPlease enter the number of characters >");
	scanf("%d",&numoc);
	pw = (char *) malloc (sizeof(char) * (numoc+1));
	if(ynans == 1){
		srand((unsigned)time(NULL));
		for(c=0;c<numoc;c++){
			r = rand()%3;
			switch(r){
				case 0:
					*(pw+c) = '0'+rand()%10;
					break;
				case 1:
					*(pw+c) = 'a'+rand()%26;
					break;
				case 2:
					*(pw+c) = 'A'+rand()%26;
					break;
				}
		}
	} else if(ynans == 0){
		srand((unsigned)time(NULL));
		for(c=0;c<numoc;c++){
			r = rand()%2;
			switch(r){
				case 0:
					*(pw+c) = '0'+rand()%10;
					break;
				case 1:
					*(pw+c) = 'a'+rand()%26;
					break;
				}
		}
	}
	*(pw+numoc) = '\0';
	printf("\tPassword : %s\n",pw);
  free(pw);
	return 0;
}
