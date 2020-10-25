#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<conio.h>
#include<dos.h>
#include<windows.h>

struct EmployStruct{
    char id[100];
    char password[100];
    char annual[100];
    char sick[100];
    char personal[100];
};
struct EmployStruct *curUser,*curType;

void updateFile(int i){
     FILE *user, *tempUser;
     int f = 0;
     user = fopen("info.txt", "r");
     tempUser = fopen("tempinfo.txt", "w");
     char id[100],password[100],annual[100],sick[100],personal[100];
    while(fscanf(user,"%s %s %s %s %s ",&id,&password,&annual,&sick,&personal)!=EOF)
     {
      if (strcmp(id,curUser->id)==0)
      {
        if(i==1){
            int ann = atoi(curUser->annual)-1;
            itoa(ann,curUser->annual,10);
            fprintf(tempUser,"%s %s %s %s %s %s",curUser->id,curUser->password,curUser->annual,curUser->sick,curUser->personal,"\n");
        }
        else if(i==2){
            int sic = atoi(curUser->sick)-1;
             itoa(sic,curUser->sick,10);
            fprintf(tempUser,"%s %s %s %s %s %s",curUser->id,curUser->password,curUser->annual,curUser->sick,curUser->personal,"\n");
        }
        else if(i==3){
            int yea = atoi(curUser->personal)-1;
            itoa(yea,curUser->personal,10);
            fprintf(tempUser,"%s %s %s %s %s %s",curUser->id,curUser->password,curUser->annual,curUser->sick,curUser->personal,"\n");
        }
      }
      else
      {
       fprintf(tempUser,"%s %s %s %s %s %s",id,password,annual,sick,personal,"\n");
      }
     }
     fclose(user);
     fclose(tempUser);

     user = fopen("info.txt", "w");
     tempUser = fopen("tempinfo.txt", "r");

     while (fscanf(tempUser,"%s %s %s %s %s ",&id,&password,&annual,&sick,&personal)!=EOF)
     {
        fprintf(user,"%s %s %s %s %s %s",id,password,annual,sick,personal,"\n");
        if(strcmp(id,curUser->id)==0){
            strcpy(curUser->id,id);
            strcpy(curUser->password,password);
            strcpy(curUser->annual,annual);
            strcpy(curUser->sick,sick);
            strcpy(curUser->personal,personal);
        }
     }
     fclose(tempUser);
     fclose(user);

}
void openFile2()
{
    char temp[100];
    char username[100];
    char type[100];
    char date[100];
    int i=0;
    FILE*ldate;
    ldate=fopen("leaveday.txt","r");
    while(fscanf(ldate,"%s %s %s ",&username,&type,&date)!=EOF){
        if(strcmp(curUser->id,username)==0)
            printf("-%8s %10s\n",type,date);
    }
    fclose(ldate);
}

void updateFile2(int i,char day[],char month[],char year[])
{

    FILE *ldate;
    ldate = fopen("leaveday.txt","a");
    char date[30];
    strcpy(date,day);
    strcat(date,"/");
    strcat(date,month);
    strcat(date,"/");
    strcat(date,year);
    strcat(date,"\n");
    if(i==1)
        fprintf(ldate,"%s %s %s",curUser->id,"annual",date);
    else if(i==2)
        fprintf(ldate,"%s %s %s",curUser->id,"sick",date);
    else if(i==3)
        fprintf(ldate,"%s %s %s",curUser->id,"personal",date);
    fclose(ldate);
    openFile2();
}

void checkDate(int i)
{
    char day[10];
    char month[10];
    char year[10];
    char date[100];
    char *token;
    int a=0;
    bool checkday=true,checkmonth=true,checkyear=true;
    printf("Enter your leave date(DD/MM/YYYY)\nex.12/01/2019 : ");
    gets(date);
    token = strtok(date," /\\");
    while(token!=NULL){
        if(a%3==0)
            strcpy(day,token);
        else if(a%3==1)
            strcpy(month,token);
        else if(a%3==2)
            strcpy(year,token);
        a++;
        token=strtok(NULL," /\\");
        }

    for(int j=0; j<strlen(day); j++){
        if (!(isdigit(day[j]))){
            checkday = false;
            break;
        }
    }
    for(int k=0; k<strlen(month); k++){
        if (!isdigit(month[k])){
            checkmonth = false;
            break;
        }
    }
    for(int l=0; l<strlen(year); l++){
        if (!isdigit(year[l])){
            checkyear = false;
            break;
        }

    }


    if(checkday && checkmonth && checkyear){
        if((atoi(month)==1 || atoi(month)==3 || atoi(month)==5 || atoi(month)==7 || atoi(month)==8 || atoi(month)==10 || atoi(month)==12) && atoi(day)>0 && atoi(day)<=31 && atoi(year)>=2019 && atoi(year)<=2021)
            {
            printf("Your leave date is %s/%s/%s \n",&day,&month,&year);
            updateFile(i);
            updateFile2(i,day,month,year);
            }
        else if((atoi(month)==4 || atoi(month)==6 || atoi(month)==9 || atoi(month)==11) && atoi(day)>0 && atoi(day)<=30 && atoi(year)>=2019&& atoi(year)<=2021)
            {
                printf("Your leave date is %s/%s/%s \n",&day,&month,&year);
                updateFile(i);
                updateFile2(i,day,month,year);
            }

        else if((atoi(month)==2) && atoi(day)>0 && atoi(day)<=28 && atoi(year)>=2019&& atoi(year)<=2021)
            {
                printf("Your leave date is %s/%s/%s \n",&day,&month,&year);
                updateFile(i);
                updateFile2(i,day,month,year);
            }
        else{
            printf("please enter a valid date.\n");
            checkDate(i);
        }
}
    else {
        printf("please enter a valid date.\n");
        checkDate(i);
    }

}

int writeFile()
{
    char id2[100],pass[100],name[100],passJa[100],Annual[20],Sick[10],Perso[100];
    FILE *fp1  ;
    fp1 = fopen("info.txt", "r");
    if(fp1 != NULL)
    {
        printf("enter new account : ");
        gets(id2);
        curUser =(struct EmployStruct*)malloc(sizeof(struct EmployStruct));
        while(fscanf(fp1,"%s %s %s %s %s",&curUser->id,&curUser->password,&curUser->annual,&curUser->sick,&curUser->personal)!=EOF)
        {
             if(strcmp(id2,curUser->id) == 0 )
             {
                 break;
             }
             else if (strcmp(id2,curUser->id) != 0 )
             {
                continue;
             }
        }
        if(strcmp(id2,curUser->id) == 0 )
        {
             printf("this account is already exist.\n");
             return 0 ;
            // printf("enter password");
            // gets(pass);
        }
        else
        {
            fp1 = fopen("info.txt","a");
            printf("enter password : ");
            gets(pass);
            fprintf(fp1,"%s %s %s %s %s %s",id2,pass,"10","30","5","\n");
            fclose(fp1);
            printf("Complete!!\n");
            return 1;
        }

    }

}

void checkLeave(){
    char input[20];
    char input2[20];

    bool annual=true,sick=true,personal=true;
    printf("------Summary of leave balance------\n");
    printf("|     Annual leave balance   :  %2s |\n",curUser->annual);
    printf("|     Sick leave balance     :  %2s |\n" ,curUser->sick);
    printf("|     Personal leave balance :  %2s |\n",curUser->personal);
    printf("------------------------------------\n\n");
    if(atoi(curUser->annual)==0)
        annual = false;
    if(atoi(curUser->sick)==0)
        sick = false;
    if(atoi(curUser->personal)==0)
        personal = false;

    printf("Would you like to take a leave (Y/N).");
    gets(input);
    input[0]=toupper(input[0]);

    if(strcmp(input,"Y")==0){
        printf(" A->Annual\n S->Sick\n P->Personal\n");
        printf("Enter your type of leave (A/S/P).");
        gets(input2);
        input2[0]=tolower(input2[0]);
        if(strcmp(input2,"a")==0){
            if(!annual)
                printf("OVERLIMIT(=0)\n");
            else{
               checkDate(1);
            }
        }
        else if(strcmp(input2,"s")==0){
            if(!sick)
                printf("OVERLIMIT(=0)\n");
            else{
               checkDate(2);
            }
        }
        else if(strcmp(input2,"p")==0){
            if(!personal)
                printf("OVERLIMIT(=0)\n");
            else{
               checkDate(3);
            }
        }
        else
            printf("Invalid input TRY AGAIN.\n");
    }
    else if (strcmp(input,"N")==0)
    {
        exit(0);
    }

    else
        printf("Invalid input try again.\n");

}

void openFile()
{
    char username[100];
    char password[100];
    bool check = true;
    FILE*fp;
    while(check){
        fp=fopen("info.txt","r");
        printf("Please enter your id : ");
        gets(username);
        curUser =(struct EmployStruct*)malloc(sizeof(struct EmployStruct));
        while(fscanf(fp,"%s %s %s %s %s",&curUser->id,&curUser->password,&curUser->annual,&curUser->sick,&curUser->personal)!=EOF)
        {
             if(strcmp(username,curUser->id) == 0 )
             {
                check = false;
                break;
             }
        }
       fclose(fp);
       if(check)
            printf("This username doesn't exist please try again\n");
    }


    if(!check){
        printf("Please enter your password : ");
        gets(password);
        if(strcmp(password,curUser->password)==0){
            printf("Login successfully \n");
        }
        else{
            printf("password doesn't match try again.\n");
           // sleep(2);
         //   system("cls");
            openFile();
        }
    }
}
void start(){
    char select[100];
    int r = 0;
    printf("*****WELCOME TO WANNAONE LIMITED*****\n");
    do
        {
            printf("Press 1.Add new account\n      2.Take leave\n      3.Show leave dates\n");
            gets(select);
            if(strcmp(select,"1") == 0)
            {
              while(r==0)
              {
                r = writeFile();
              }
               break;
            }
            else if(strcmp(select,"2")== 0 )
            {
                openFile();
                checkLeave();
                break;
            }
            else if(strcmp(select,"3")== 0 ){
                openFile();
                openFile2();
                break;
            }
            else
                printf("Invalid input try again\n");
        }while(strcmp(select,"1")!= 0 && strcmp(select,"2")!= 0 && strcmp(select,"3")!=0);


}
int main()
{
    char input[100];
    do{
        start();
        printf("Would you like to continue (Y/N) : ");
        gets(input);
        input[0]=toupper(input[0]);
        system("cls");
    }while(strcmp(input,"Y")==0);

}
