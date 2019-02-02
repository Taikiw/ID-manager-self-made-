#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#define MAXCNT 100

typedef struct Manager{
  char Name[30];
  char AccountID[100];
  char MailAdress1[100];
  char MailAdress2[100];
  char PassWord[100];
  struct Manager *nextmgr;
}Mgr;

int Startmenu(void);
Mgr *LoadingFile(Mgr *);
int Registration(Mgr *,Mgr *,int);
int Swinput(Mgr *,int);
int Fileoutput(Mgr *);
int DisplayList(Mgr *); //Display Password List
int OTPMaker(void); //Onetime Password Maker
int Selectyn(void); //Checking select answer

int main(void){
  int select,selru,numor; //numor : number of registration
  char update[30];
  Mgr *mgrp; //Manager pointer
  Mgr *nextstartp;
  mgrp = (Mgr *)malloc(sizeof(Mgr));
  select = Startmenu();
  printf("\n");
  switch(select){
    case 0:
      nextstartp = LoadingFile(mgrp);
      printf("\tPlease enter the number of regstrations >");
      scanf(" %d",&numor);
      while(numor <= 0){
        printf("\tRe : Please enter the number of regstrations >");
        scanf(" %d",&numor);
      }
      Registration(mgrp,nextstartp,numor);
      printf("\tEND\n");
      break;
    case 1:
      nextstartp = LoadingFile(mgrp);
      if(mgrp == nextstartp){
        printf("\tCannot Continue\n");
        break;
      }
      DisplayList(mgrp);
      break;
    case 2:
      OTPMaker();
      break;
    case 3:
      printf("\tEND\n");
      break;
    default:
      return -1;
  }
  return 0;
}

int Startmenu(){
  int select;
  system("cls");
  printf("\n");
  printf("                ----------------------------------------------------\n");
  printf("                          ----- ID MANAGER START MENU ----          \n");
  printf("                ----------------------------------------------------\n");
  printf("\tRegistration :0 Display Password List :1 Making Onetime Password :2 END :3 >");
  scanf(" %d",&select);
  while(select < 0 || 3 < select){
		printf("\tRe: Registration :0 Display Password List :1 Making Onetime Password :2 END :3 >");
		scanf(" %d",&select);
	}
  return select;
}
Mgr *LoadingFile(Mgr *lmgrp){
  int selans,load; //sel : Select answer
  Mgr *nextlmgrp;
  Mgr *retmgrp;
  FILE *lfp; //Loading file pointer
  printf("\tIs that the first time for you to use this ? Yes : y or No : n >");
  selans = Selectyn();
  if(selans == 1){
    if((lfp=fopen("ID_data.txt","w"))==NULL){
      printf("\tCannot Open\n");
      exit(0);
    }
    printf("\tMaking new file ID_data.txt\n");
    fclose(lfp);
  }else if(selans == 0){
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
      return lmgrp;
    }
    lmgrp = lmgrp->nextmgr;
  }
  fclose(lfp);
  printf("\tFinish Loading\n");
  retmgrp = lmgrp->nextmgr;
  return retmgrp;
}
int Registration(Mgr *startmgrp,Mgr *rmgrp,int numor){
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
      printf("--------------------------------------------------------------\n");
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
      printf("--------------------------------------------------------------\n");
      break;
    default:
      return -1;
  }
  return 0;
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
    printf("\tStorage Complete\n");
  }else{
    printf("\tCannot File Delete\n");
    exit(0);
  }
  return 0;
}
int DisplayList(Mgr *dmgrp){
  Mgr *next;
  while(dmgrp->nextmgr != NULL){
    printf("--------------------------------------------------------------\n");
    printf("\tSite Name : %s\n",dmgrp->Name);
    printf("\tAccount ID : %s\n",dmgrp->AccountID);
    printf("\tMail Adress1 : %s\n",dmgrp->MailAdress1);
    printf("\tMail Adress2 : %s\n",dmgrp->MailAdress2);
    printf("\tPass Word : %s\n",dmgrp->PassWord);
    if(dmgrp->nextmgr != NULL){
      next = dmgrp->nextmgr;
      free(dmgrp);
      dmgrp = next;
    }
  }
  free(dmgrp);
  printf("--------------------------------------------------------------\n");
  printf("\t* Finish *\n");
  return 0;
}
int OTPMaker(){
	int oynans,numoc,c,r; //numoc : Number of characters
	char *pw;
	printf("\tIncluding upper case letter ? Yes : y or No : n >");
  oynans = Selectyn();
	printf("\tPlease enter the number of characters >");
	scanf("%d",&numoc);
	pw = (char *) malloc (sizeof(char) * (numoc+1));
	if(oynans == 1){
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
	} else if(oynans == 0){
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
	printf("\tOnetime Password : %s\n",pw);
  free(pw);
	return 0;
}
int Selectyn(){
  char selectyn;
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
}
