#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
//FindPhoneNumber function does the following tasks:
//checks whether a given phone number is there in the database.i.e, in the BST or not.
//returns 1 if the phone number is not in the database and 0 otherwise	
int FindPhoneNumber(BST *root, char *phoneNumber,int check)
{
	if(root==NULL)
	{
		return check;
	}
	else if(strcmp(root->MobNo,phoneNumber)==0)		//checking whether phone number is present in the database.i.e., in the BST or not
	{
	    int i=0;						//printing the details of the person with the given phone number if it is in the database
	    printf("%s",root->name);	
		for(i=0;i<40-strlen(root->name);i++) printf(" ");
		printf("%s",root->MobNo);
		for(i=0;i<20-strlen(root->MobNo);i++) printf(" ");
		printf("%s",root->Address);
		for(i=0;i<80-strlen(root->Address);i++) printf(" ");
		printf("%s",root->LastUse);
		printf(BLU"\n<------------------->\n"RESET);
	    return 0;
	}
	else
	{
		if(root->left!=NULL)
			check=FindPhoneNumber(root->left,phoneNumber,check);	//recursion
		if(root->right!=NULL)	
			check=FindPhoneNumber(root->right,phoneNumber,check);	//recursion
	}
	return check;
}
//----------------------------------------------------------------------------------------------------------
//isChar function does the following tasks:
//checks whether there is any character in the mobile number or not
//returns 1 if there is any character in the mobile number and 0 otherwise
int isChar(char a[])
{
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]-48<0 || a[i]-48>9)
        {
            if(a[i]!=43) return 1;
        }
    }
    return 0;
}	
//----------------------------------------------------------------------------------------------------------
//checkValidity function does the following tasks:
//checks whether the length of the phone number is 10 and all the digits in the mobile number are numbers only
//returns 0 if the phone number is invalid and 0 otherwise
//internally calls a subfunction.i.e.,isChar
int checkValidity(char number[])
{
    if(strlen(number)==13 && isChar(number)!=1)		
    return 0;
    else return 1;	
}
//----------------------------------------------------------------------------------------------------------
//function for searching mobile number in the BST data structure
//this function internally calls 2 subfunctions.i.e.,checkValidity and FindPhoneNumber	
void Search(BST *list){
	char phoneNumber[14],s1[14]={"+91"};
	int check=1;
	
	printf("Please enter customer's phone number\n");
	scanf("%s",phoneNumber);			//taking user input
	
	if(phoneNumber[0]!='+'||phoneNumber[1]!='9'||phoneNumber[2]!='1'){
	strcat(s1,phoneNumber);
	strcpy(phoneNumber,s1);}
	
	int flag=checkValidity(phoneNumber);		//checking whether the user's input is a valid phone number or not
	if(flag==1){					//checking if the phone number entered is invaid
		for(int i=0;i<2;i++){			//allowing the user to enter a valid phone number giving 2 extra chances
			printf("You have entered an invalid phone number.\n");
			printf("Please enter a valid phone number\n");
			scanf("%s",phoneNumber);
			flag=checkValidity(phoneNumber);//each time the user has entered a phone number, checking the validity of the phone number
			if(flag==0)break;		//if the phone number entered is valid then breaking out from the loop
			}
		}
	if(flag==0)					//if the user has entered a valid phone number then checking whether the phone number is registered or not
	{   
	    check=FindPhoneNumber(list,phoneNumber,check);//checking whether the given phone number is there in the database or not
	    if(check==1)
	        printf("You are not a registered member of our telecommunication family\n");
	   	}

}	
//----------------------------------------------------------------------------------------------------------
