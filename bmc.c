#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

struct bank  
{int accno;  
char name[20];  
float bal;  
};

typedef struct bank bank;

void menu()
{
   printf("--------------------------------------------------------------------------------------------\n");
   printf("                                  BANK MANAGEMENT SYSTEM                                    \n");
   printf("--------------------------------------------------------------------------------------------\n");
   printf("                                            MENU                                            ");
   printf("\n\n\n1.CREATE NEW ACCOUNT");
   printf("\n2.VIEW DETAILS OF ALL ACCOUNTS");
   printf("\n3.VIEW DETAILS OF A GIVEN ACCOUNT"); 
   printf("\n4.DEPOSIT");
   printf("\n5.WITHDRAW");
   printf("\n6.DELETE BANK ACCOUNT");
}


void out(bank b) //To display contents of the structure bank
{
  printf("\nAccount number: %d",b.accno);
  printf("\nName: %s",b.name);
  printf("\nBalance: %.2f",b.bal);
}

int check(int a) //to check if given account number exists- return 1 if it exists else 0
{
   int c;
   FILE *f;
   bank b;
   f= fopen("bankk.bin","rb");
   if ( f== NULL)
   {
   printf("file failed to open");
   }
   else
   {
   while(!feof(f))
   {
      fread(&b,sizeof(bank),1,f);
      if(b.accno==a)
      return 1;
   }
   }
   return 0;
   fclose(f);
}

void create()
{
      FILE *f;
      bank b;
      int x=0;
      while(x==0)
      {
         printf("\nAccno: ");
         scanf("%d",&b.accno);
         if(check(b.accno))
         {
            printf("\nAccount already exits!\nTry another");
            x=0;
         }
         else
         x=1;
      } 
      printf("\nName: ");
      scanf("%s",b.name);
      printf("\nEnter the first deposit: ");
      scanf("%f",&b.bal);
      f=fopen("bankk.bin","ab");
      fwrite(&b,sizeof(bank),1,f);
      fclose(f);
}

void view()
{
   FILE *f;
   bank b;
   int x;
   int c=0; //Allows you to re-enter the account number 5 times if the account number inputed doesn't exist
   while(c!=5)
   {
      printf("\nEnter the account number: ");
      scanf("%d",&x);
      int y=check(x);
      if(!y)
      {
         printf("\nAccount does not exist!");
         c++;
      
     if(c==5)
     {
        printf("\nTOO MANY TRIES\nLOGGING OUT");
        exit(0);
     }
      }
      else
      break;
   }
   f=fopen("bankk.bin","rb");
   while(!feof(f))
   { fread(&b,sizeof(bank),1,f);
     if(b.accno==x)
     { out(b);
       break;
     }
   }
}

void view_all()
{
   FILE *f;
   bank b;
   f=fopen("bankk.bin","rb");
   while(!feof(f))
   { fread(&b,sizeof(bank),1,f);
      if(feof(f))
      break;
      else 
      {
         out(b);
         printf("\n************************************");
         printf("\n\n");
      }
   }
}

void deposit()
{
   bank b;
   FILE *f;
   int n,x,c=0;
    while(c!=5) //Gives 5 tries to input account number
   {
      printf("\nEnter the account number: ");
      scanf("%d",&n);
      int y=check(n);
      if(!y)
      {
         printf("\nAccount does not exist!");
         c++;
      
     if(c==5)
     {
        printf("\nTOO MANY TRIES\nLOGGING OUT");
        exit(0);
     }
      }
      else
      break;
   }
   printf("\nEnter the amount to be deposited: ");
   scanf("%d",&x);
   f=fopen("bankk.bin","rb+");
   while(!feof(f))
   {
      fread(&b,sizeof(bank),1,f);
      if(b.accno==n)
      {
         b.bal+=x;
         printf("\nNew balance is: %f",b.bal);
         fseek(f,-1*(sizeof(bank)), 1);
         fwrite(&b, sizeof(bank), 1, f);
         break;
      }
   }
   fclose(f);
}

void withdraw()
{
   int n,x,c=0;
    while(c!=5) //Gives 5 tries to input account number
   {
      printf("\nEnter the account number: ");
      scanf("%d",&n);
      int y=check(n);
      if(!y)
      {
         printf("\nAccount does not exist!");
         c++;
      
         if(c==5)
        {
        printf("\nTOO MANY TRIES\nLOGGING OUT");
        exit(0);
        }
      } 
      else
      break;
   }
   printf("\nEnter the amount to be withdrawn: ");
   scanf("%d",&x);
   bank b;
   FILE *f;
   f=fopen("bankk.bin","rb+");
   while(!feof(f))
   {
      fread(&b,sizeof(bank),1,f);
      if(b.accno==n)
      {
         if(b.bal<x)
         printf("\nLow balance");
         else
         {
            b.bal-=x;
            printf("\nNew balance is: %f",b.bal);
            fseek(f,-1*(sizeof(bank)), 1);
            fwrite(&b, sizeof(bank), 1, f);
         }
         break;
      }
   }
   fclose(f);
}

void delete()
{
   int n,c=0;
    while(c!=5) //Gives 5 tries to input account number
   {
      printf("\nEnter the account number: ");
      scanf("%d",&n);
      int y=check(n);
      if(!y)
      {
         printf("\nAccount does not exist!");
         c++;
      
     if(c==5)
     {
        printf("\nTOO MANY TRIES\nLOGGING OUT");
        exit(0);
     }
      }
      else
      break;
   }
   FILE *f,*f1;
   f=fopen("bankk.bin","rb");
   f1=fopen("temp.bin","wb");
   while(!feof(f))
   {
      bank b;
      fread(&b,sizeof(bank),1,f);
      if(b.accno!=n)
      {
         fwrite(&b,sizeof(bank),1,f1);
      }
   }
   remove("bankk.bin");
   rename("temp.bin","bankk.bin");
   printf("\nAccount deleted!");
   fclose(f1);
}

void main()
{
   int ans=1;
   while(ans)
   { system("clear");
     menu();
     printf("\nEnter your choice: ");
     scanf("%d",&ans);
     switch(ans)
     {
        case 1: create();
                break; 
        case 2: view_all();
                break;
        case 3: view();
                break;
        case 4: deposit();
                break;
        case 5: withdraw();
                break;
        case 6: delete();
     } 
     printf("\nPress any number (0 to exit, else continue): ");
     scanf("%d",&ans);
   }
}
