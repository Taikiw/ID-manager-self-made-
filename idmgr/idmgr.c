#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#define MAXCNT 100
<<<<<<< HEAD
<<<<<<< HEAD
// #define CK printf("===%d===",__LINE__);
=======
#define CK printf("===%d===",__LINE__);
>>>>>>> 17b5820ff03f4ce5f9ac156048a90b5b9bac58c8
=======
#define CK printf("===%d===",__LINE__);
>>>>>>> 17b5820ff03f4ce5f9ac156048a90b5b9bac58c8
typedef struct Manager{
  char Name[30];
  char AccountID[100];
  char MailAdress1[100];
  char MailAdress2[100];
  char Password[100];
  struct Manager *nextmgr;
}Mgr;

int IDMGR(void);
int Startmenu(void);
Mgr *LoadingFile(Mgr *);
int Registration(Mgr *,Mgr *);
int Administration(Mgr *);
int Swinput(Mgr *,int);
int Fileoutput(Mgr *);
int DisplayList(Mgr *,int); //Display Password List
Mgr *Search(Mgr *,int);
int Change(Mgr *);
int Delete(Mgr *);
Mgr *LinkingData(Mgr *,int);
int PwG(void); //Password Generator
int Select(int); //Checking select answer

int main(void){
  int selectmain,mode=0;
  printf("\tWhich one do you want to start ?\n");
  printf("\tPlease Enter your selected number.\n"); //Please enter a number of to select
  printf("\n");
  printf("\tID MANAGER :'0' Password Generator :'1' > ");
  selectmain = Select(mode);
  switch(selectmain){
    case 0:
      IDMGR();
      break;
    case 1:
      PwG();
      break;
    default:
      return -1;
  }
  return 0;
}

int IDMGR(void){
  int selectmenu,mode=1,smode=0;
  Mgr *hmgrp;
  Mgr *nextmgrp;
  hmgrp = (Mgr *)malloc(sizeof(Mgr));
  nextmgrp = LoadingFile(hmgrp);
  selectmenu = Startmenu();
  switch(selectmenu){
    case 0:
      Registration(hmgrp,nextmgrp);
      break;
    case 1:
      Administration(hmgrp);
      break;
    case 2:
      if(hmgrp == nextmgrp){
        printf("\tCannot Continue.\n");
        return -1;
      }
      DisplayList(hmgrp,smode);
      break;
    case 3:
      printf("\tEND.\n");
      break;
    default:
      return -1;
  }
  return 0;
}

int Startmenu(void){
  int mode=1;
  // system("cls");
  printf("\n");
  printf("                ----------------------------------------------------\n");
  printf("                          ----- ID MANAGER START MENU ----          \n");
  printf("                ----------------------------------------------------\n");
  printf("\n");
  printf("\tRegistration :'0' Change management :'1' Display Password List :'2' END :'3' > ");
  return Select(mode);
}

Mgr *LoadingFile(Mgr *lmgrp){
  int afsearch,load; //afserch : available flie search
  Mgr *nextlmgrp;
  Mgr *retmgrp; //ret : return
  FILE *lfp; //Loading file pointer
  if((lfp=fopen("ID_data.txt","r")) != NULL){
    afsearch = 1;
  }else{
    afsearch = 0;
  }
  fclose(lfp);
  switch(afsearch){
    case 0:
      if((lfp=fopen("ID_data.txt","w")) == NULL){
        printf("\tCannot Open\n");
        exit(0);
      }
      fclose(lfp);
      IDMGR();
      exit(0);
    case 1:
      printf("\tData Loading...\n");
      if((lfp=fopen("ID_data.txt","r")) == NULL){
        printf("\tCannot Open.\n");
        exit(0);
      }
      for(load=0;load<MAXCNT;load++){
        lmgrp->nextmgr = (Mgr*)malloc(sizeof(Mgr));
        nextlmgrp = lmgrp->nextmgr;
        nextlmgrp->nextmgr = NULL;
        if(fscanf(lfp,"%[^,],%[^,],%[^,],%[^,],%s\n",lmgrp->Name,lmgrp->AccountID,lmgrp->MailAdress1,lmgrp->MailAdress2,lmgrp->Password)==EOF){
          free(lmgrp->nextmgr);
          lmgrp->nextmgr = NULL;
          fclose(lfp);
          printf("\tFinish Loading.\n");
          return lmgrp;
        }
        lmgrp = lmgrp->nextmgr;
      }
      fclose(lfp);
      printf("\tFinish Loading.\n");
      retmgrp = lmgrp->nextmgr;
      return retmgrp;
  }
  return NULL;
}

int Registration(Mgr *hmgrp,Mgr *rmgrp){
  int reg,numor,inp,mode=2; //numor : Number of registrtions
  printf("\n");
  printf("      \tDATA REGISTER\n");
  printf("\tPlease enter the number of regstrations. > ");
  numor = Select(mode);
  printf("\n");
  printf("-------------------------------------------------------------\n");
  printf("     \t** ATTENTION **\n");
  printf("\tIf there is nothing to enter , please enter 'no'\n\n");
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
  printf("\tRegistration Complete.\n");
  Fileoutput(hmgrp);
  return 0;
}

int Administration(Mgr *hmgrp){
  int selectadmin,mode=3;
  printf("\n");
  printf("      \t*** Setting of ID MANAGER ***\n");
  printf("\tContent Change :'0' Content Delete '1' > ");
  selectadmin = Select(mode);
  switch(selectadmin){
    case 0:
      Change(hmgrp);
      break;
    case 1:
      Delete(hmgrp);
      break;
    default:
      return -1;
  }
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
      printf("\tPassword >");
      scanf(" %s",swmgrp->Password);
      printf("-------------------------------------------------------------\n");
      break;
    default:
      return -1;
  }
  return 0;
}

int DisplayList(Mgr *dmgrp,int smode){
  int data=1;
  Mgr *next;
  switch(smode){
    case 0:
      while(dmgrp->nextmgr != NULL){
        printf("--------------------------------------------------------------\n");
        printf("\tSite Name : %s\n",dmgrp->Name);
        printf("\tAccount ID : %s\n",dmgrp->AccountID);
        printf("\tMail Adress1 : %s\n",dmgrp->MailAdress1);
        printf("\tMail Adress2 : %s\n",dmgrp->MailAdress2);
        printf("\tPassword : %s\n",dmgrp->Password);
        if(dmgrp->nextmgr != NULL){
          next = dmgrp->nextmgr;
          free(dmgrp);
          dmgrp = next;
        }
        data++;
      }
      free(dmgrp);
      printf("--------------------------------------------------------------\n");
      printf("\t* Finish *\n");
      break;
    case 1:
      while(dmgrp->nextmgr != NULL){
        printf("--------------------------------------------------------------\n");
        printf("\tSite Name [data %d ] : %s\n",data,dmgrp->Name);
        if(dmgrp->nextmgr != NULL){
          next = dmgrp->nextmgr;
          dmgrp = next;
        }
        data++;
      }
      printf("--------------------------------------------------------------\n");
      printf("\t* Finish *\n");
      break;
    case 2:
      printf("--------------------------------------------------------------\n");
      printf("\tSite Name : %s\n",dmgrp->Name);
      printf("\tAccount ID : %s\n",dmgrp->AccountID);
      printf("\tMail Adress1 : %s\n",dmgrp->MailAdress1);
      printf("\tMail Adress2 : %s\n",dmgrp->MailAdress2);
      printf("\tPassword : %s\n",dmgrp->Password);
      printf("--------------------------------------------------------------\n");
      break;
    }
  return data;
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
    fprintf(cpyfp,"%s\n",fomgrp->Password);
    if(fomgrp->nextmgr != NULL){
      nextfomgrp = fomgrp->nextmgr;
      free(fomgrp);
      fomgrp = nextfomgrp;
      CK;
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
    return -1;
  }
  return -1;
}

Mgr *Search(Mgr *smgrp,int f){
  int sc; //search counter
  Mgr *nextsmgrp;
  for(sc=1;sc<f;sc++){
    nextsmgrp = smgrp->nextmgr;
    smgrp = nextsmgrp;
  }
  return smgrp;
}

int Change(Mgr *hmgrp){
  int cd,cf,inp,mode=6,smode=1;
  Mgr *precmgrp;
  Mgr *cmgrp;
  Mgr *nextcmgrp;
  cd = DisplayList(hmgrp,smode);
  printf("\tPlease enter a number of you want to change. > ");
  cf = Select(mode);
  if((cf-1) == 0){
    cmgrp = hmgrp;
  }else{
    precmgrp = Search(hmgrp,(cf-1));
    cmgrp = Search(hmgrp,cf);
  }
  smode=2;
  DisplayList(cmgrp,smode);
  nextcmgrp = cmgrp->nextmgr;
  printf("\tIf there is nothing to Change , please enter 'no'\n");
  for(inp=0;inp<5;inp++){
    Swinput(cmgrp,inp);
    printf("\n");
  }
  precmgrp->nextmgr = cmgrp;
  cmgrp->nextmgr = nextcmgrp;
  hmgrp = LinkingData(hmgrp,cd);
  Fileoutput(hmgrp);
  printf("\t***Update Complete***\n");
  return 0;
}

int Delete(Mgr *hmgrp){
  int cd,delf,mode=7,smode=1;
  Mgr *predelmgrp;
  Mgr *delmgrp;
  Mgr *nextdelmgrp;
  cd = DisplayList(hmgrp,smode);
  printf("\tPlease enter a number of you want to delete. > ");
  delf = Select(mode);
  if(delf-1 == 0){
    predelmgrp = hmgrp->nextmgr;
    free(hmgrp);
    printf("\t***Delete Complete***\n");
    hmgrp = LinkingData(hmgrp,(cd-1));
    Fileoutput(hmgrp);
  }else{
    predelmgrp = Search(hmgrp,(delf-1));
    delmgrp = Search(hmgrp,delf);
    nextdelmgrp = delmgrp->nextmgr;
    free(delmgrp);
    predelmgrp->nextmgr = nextdelmgrp;
    printf("\t***Delete Complete***\n");
    hmgrp = LinkingData(hmgrp,(cd-1));
    Fileoutput(hmgrp);
  }
  return 0;
}

Mgr *LinkingData(Mgr *hmgrp,int cd){
  int data;
  Mgr *linkmgrp;
  Mgr *nextlink;
  linkmgrp = hmgrp;
  for(data=1;data<cd;data++){
    nextlink = linkmgrp->nextmgr;
    linkmgrp = nextlink;
  }
  linkmgrp= NULL;
  return hmgrp;
}

int PwG(void){
	int selectyn,numoc,c,r,mode=4; //numoc : Number of characters
	char *pw;
  system("cls");
  printf("\n");
  printf("                ----------------------------------------------------\n");
  printf("                            ----- PASSWORD GENERATOR -----          \n");
  printf("                ----------------------------------------------------\n");
  printf("\n");
	printf("\tIncluding upper case letter ? Yes : '1' or No : '0' >");
  selectyn = Select(mode);
	printf("\tPlease enter the number of characters >");
  mode = 5;
  numoc = Select(mode);
	pw = (char *) malloc (sizeof(char) * (numoc+1));
	if(selectyn == 1){
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
	} else if(selectyn == 0){
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

int Select(int mode){
  int select;
  scanf("%d",&select);
  switch(mode){
    case 0:
      while(select < 0 || 1 < select){
        printf("\tRe: ID MANAGER :'0' Password Generator :'1' >");
        scanf(" %d",&select);
      }
      return select;
    case 1:
      while(select < 0 || 3 < select){
        printf("\tRe: Registration :'0' Change management :'1' Display Password List :'2' END :'3' >");
        scanf(" %d",&select);
      }
      return select;
    case 2:
      while(select <= 0){
        printf("\tRe : Please enter the number of regstrations. >");
        scanf(" %d",&select);
      }
      return select;
    case 3:
      while(select < 0 || 1 < select){
        printf("\tRe : Content Change :'0' Content Delete '1' > ");
        scanf(" %d",&select);
      }
      return select;
    case 4:
      if(select == 1){
        return 1;
      }else if(select == 0){
        return 0;
      }else if((select != 1) && (select != 0)){
        printf("\tRe: Yes : '1' or No : '0' >");
        return Select(mode);
      }
      return 1;
    case 5:
      while(select <= 0){
        printf("\tRe : Please enter the number of characters. >");
        scanf(" %d",&select);
      }
      return select;
    case 6:
      while(select <= 0){
        printf("\tRe : Please enter the number of you want to change. >");
        scanf(" %d",&select);
      }
      return select;
    case 7:
      while(select <= 0){
        printf("\tRe : Please enter the number of you want to delete. >");
        scanf(" %d",&select);
      }
      return select;
    default:
      return -1;
  }
  return 0;
}
