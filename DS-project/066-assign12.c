#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include "017assign12.c"
#define Size (53)
#define KRED  "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define CYN  "\x1B[36m"
#define NRM  "\x1B[0m"
#define BLU  "\x1B[34m"
#define RESET "\x1B[0m"


/*
returns number of days between present date from january of that particular year
*/
int month(int a,int yy,int mon[]){
    int x=0,c;
    for(c=0;c<a-1;c++){
        if(c==1){
            if(yy%4==0)
                        x+=29;
            else
                x+=28;
     }
   else
      x+=mon[c];
   }
   return(x);
 }
 /*
This function finds difference between the two dates and sends number of days
 */
int days(int y1,int y2,int m1,int m2,int d1,int d2){

   int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
   int count=0,i;
   for(i=y1;i<y2;i++){
		 			//leap year
          if(i%4==0)
              count+=366;
          else
            count+=365;
   }
   count-=month(m1,y1,mon);//subract days from beginning
   count-=d1;
   count+=month(m2,y2,mon);//add days in present year
   count+=d2;
   if(count<0)
          count=count*-1;
   return count;
 }
/*This function exact last recharged date and present date and sends it to the function called::days
 to calculate number of days between these days */
int check_date(BST *list){

      char dateLast[10],a[4];
      int i,j,k=0,cc=0;
      int a1,a2,b1,b2,c1,c2;
      strcpy(dateLast,list->LastUse);
			/*Extracting last recharge date from the node of BST tree*/
      a1=(dateLast[0]-'0')*10+(dateLast[1]-'0');//date
      b1=(dateLast[3]-'0')*10+(dateLast[4]-'0');//month
      c1=(dateLast[6]-'0')*1000+(dateLast[7]-'0')*100+(dateLast[8]-'0')*10+(dateLast[9]-'0');//year


      int daysB;
			/*this part is to get the present days*/
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      a2=tm.tm_mday;//present date
      b2=tm.tm_mon + 1;//present month
      c2=tm.tm_year + 1900;//present year
			//year c2 is greater than c1
      if(c2>=c1)
              daysB=days(c1,c2,b1,b2,a1,a2);
			//if year c1 is greater than c2
      else
          daysB=days(c2,c1,b2,b1,a2,a1);

			/*returns 1:
					 			if last ercharge is between 60 to 90 days(2 to 3 months)
					else :
							return 0
			*/
        
      if(daysB>=60 && daysB<=90 ){
      		//  printf("%d\n",daysB);		number of days for which it is not used
        	list->Datediff=daysB;
  				return 1;
      }

      else
        return 0;

}
/*This function sends the message to the defaulter about recharge and also sends some offer*/
void printMessage(BST *list){
  	printf("\n");
		//sending message to customer if he is a defaulter
    printf(YEL"\t_____________________________________________________________________\n");
    printf("\t|"RESET KRED"DEAR %s"RESET,list->name);
    for(int x=0;x<63-strlen(list->name);x++)
      printf(" ");
      printf(""YEL"|\n"RESET);
    printf(YEL"\t|"RESET"                                                                  "YEL"  |\n"RESET);
    printf(YEL"\t|"RESET"\tUR no"GRN" %s"RESET" didnot recharge your No after"GRN" %s"RESET"  "YEL"  |\n"RESET,list->MobNo,list->LastUse);
    printf(YEL"\t|"RESET"\tPlease recharge with-in  %d  days to avail your number      "YEL" |\n"RESET,90-list->Datediff);
    printf(YEL"\t|"RESET"\tAfter %d days your number will be de-activated              "YEL" |\n   "RESET,90-list->Datediff);
    printf(YEL"\t|____________________________________________________________________|\n\n\n\n"RESET);
		/*sending offer to the customer*/
		printf(YEL"\t_____________________________________________________________________\n");
    printf("\t|"RESET KRED"Dear customer                                                       "YEL"|\n"RESET,list->name);
    printf(YEL"\t|"RESET"                                                                  "YEL"  |\n"RESET);
    printf(YEL"\t|"RESET"\tOFFER!!! "YEL"                                                    |\n"RESET,list->MobNo,list->LastUse);
    printf(YEL"\t|"RESET"\tRs349=28GB(1GB/day)+UNTD CALL, 28 days     "YEL"                  |\n"RESET,90-list->Datediff);
    printf(YEL"\t|"RESET"\tRs244=Unlimited Calls+1GB/day,70 days  Click:"KRED" stark.com/5/m"YEL"  |\n   "RESET,90-list->Datediff);
    printf(YEL"\t|____________________________________________________________________|\n\n\n\n"RESET);

}
/*This function check which user is a defaulter and if customer is defaulter then calls a function to send message */
void getDate(BST *list){
  if(list!=NULL){
		//check_date function checks number of days
		//if 60<=days<=90 check_date=1: else 0
      if(check_date(list))
            printMessage(list);//send message to customer if check_date returns 1

      getDate(list->left);
      getDate(list->right);
		}
  }
/*
int main(){
BST *list = (BST*)malloc(sizeof(BST));
list = NULL;
TRIE *trie = getNode();
printf("select 5 to see my work\n\n");
Start(list,trie);

return 0;
}
*/
