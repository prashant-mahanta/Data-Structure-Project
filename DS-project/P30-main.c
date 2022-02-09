
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#define Size (53)
#define KRED  "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define CYN  "\x1B[36m"
#define NRM  "\x1B[0m"
#define BLU  "\x1B[34m"
#define RESET "\x1B[0m"
//Defining a BST tree structure with 5 fields
typedef struct Bst{
	char name[50];
	char MobNo[14];
	char Address[100];
	char LastUse[10];
	int Datediff;
	struct Bst *left;
	struct Bst *right;
	}BST;
//creating a trie data structure
typedef struct Trie{
	struct Trie *child[Size];
	bool IsLeaf;
	}TRIE;

char name[100];
int x=0,co=0;

//-------*********djkjkjdkkdjjkj---------------------------------------------------------------------------------------------------
//C2I function does the following tasks:
//Converts a character to an integer by converting:
//lower case characters to integers from 0-25
//space to 26
//uppercase characters to integers in the inclusive range of 27-53
int C2I(char ch){
	if((int)ch==32)
		return 26;
	else if((int)ch>=65&&(int)ch<=90)
		return (int)ch-38;
	else
		return (int)ch - (int)'a';
	}
	//----------------------------------------------------------------------------------------------------------

	//Function to print all the records.i.e., the elements of the BST in INORDER traversal

	//getNode function initializes a trie node and subsequently fills it


TRIE *getNode(){
	TRIE *cnode = (TRIE*)malloc(sizeof(TRIE));	//dynamically allocating space to a trie node
	if(cnode){																				//checking if the space has been allocated to the trie node(cnode) or not
		int i;
		cnode->IsLeaf = false;
		for(i=0;i<Size;i++)															//initialising all the character pointers of the character pointer array as null
			cnode->child[i]=NULL;
		}
	return cnode;																			//returning the head of the trie
}

//----------------------------------------------------------------------------------------------------------
//insertTrie function does the following task:
//inserts a name to the trie data structure
void insertTrie(TRIE *root, const char *key){
	int level,index,length;
	length = strlen(key);				//storing the length of the key(name to be inserted into the trie) in length

	TRIE *cnode = root;
	for(level = 0;level<length;level++){		//each time while traversing through the trie checking whether there is a node or not
		index = C2I(key[level]);		//if there is not a node then calling the function getNode for allocating space to a new trie node
		if(!cnode->child[index])
			cnode->child[index] = getNode();
		cnode = cnode->child[index];
	}
	cnode->IsLeaf = true;				//initialising IsLeaf=true marking the end of the word in the trie
}



//For each name whose prefix is the prefix entered by the user, this fuction prints all the details corresponding to that name.
void PrintDetails(BST *head,char str[]){
	if(head == NULL)
		return;
	else if(strcmp(head->name,str)==0){
		int i=0;
	    printf("%s",head->name);
		for(i=0;i<30-strlen(head->name);i++) printf(" ");
		printf("%s",head->MobNo);
		for(i=0;i<20-strlen(head->MobNo);i++) printf(" ");
		printf("%s",head->Address);
		for(i=0;i<80-strlen(head->Address);i++) printf(" ");
		printf("%s",head->LastUse);
		printf(BLU"\n<------------------->\n"RESET);

		}
	PrintDetails(head->left,str);
	PrintDetails(head->right,str);

	}
//----------------------------------------------------------------------------------------------------------
//FindName function does the following task:
//prints all the names which share a common prefix
void FindName(BST *head,TRIE *trie, char str[]){
	int i=0;
	static int j=0;
	if(trie!=NULL){
	while(i<53){
		if(trie->child[i]!=NULL){
		if(i==26)
			name[x]=32;	//if i=26 then store 32 in name(space)
		else if(i>26)
			name[x]=i+38;	//if i>26 then store i+38 in name(uppercase alphabets)
		else
			name[x]=i+97;	//if i<26 then store i+97 in name(lowercase alphabets)
		x++;
		FindName(head,trie->child[i],str);	//recursion
		x--;
		}
	i++;
		}
	}
	if(trie->IsLeaf==true){			//if one word is completed then end the sring and subsequently print the details of the person with the name
		name[x]='\0';
		PrintDetails(head,name);
		return;
	}
}
//----------------------------------------------------------------------------------------------------------
//search function does the following tasks:
//checks whether a given name is there in the trie or not
//returns 1 if it is in the trie and 0 otherwise
int search(TRIE *root, const char *key) {
    int level, length, index;
    length = strlen(key);
    TRIE *temp;
    TRIE *trie = root;

    for (level = 0; level < length; level++) {	//checking whether a name is there in the trie or not
        index = C2I(key[level]);
        if (!trie->child[index])
            return 0;				//if it is not in the trie then return 0
        temp = trie;
        trie = trie->child[index];		//recursion
    }

    return 1;					//if it is in the trie then return 1
}
//----------------------------------------------------------------------------------------------------------
//Trie function does the following task:
//stores the prefix given by the user in a character array str
//traverses in the trie till the traversed length = length of str, each time storing the address of the trie node in trie
//calling a function FindName which prints all the names whose prefix is name in str alongwith details of the person with the name
void Trie(BST *list, TRIE *trie){
	char str[50];
	int i=0,index=0;
	printf("Enter customer's name\n");
	scanf(" %[^\n]s",str);
	x=0;
	for(x=0;x<strlen(str);x++)
		name[x]=str[x];			//copying str in name
	if(search(trie,str)==1){		//checking whether the name in str is there in the trie or not
		for(i=0;i<strlen(str);i++){	//going to the level in the trie upto the end of the prefix
			index = C2I(str[i]);
			trie = trie->child[index];
			}
			system("clear");
		printf("Search Results..\n\n");
		FindName(list,trie,str);		//calling function FindName
	}
	else
		printf("\nSorry, the name doesn't	 exist.\n");
}
//----------------------------------------------------------------------------------------------------------
void PrintRecords(BST *list){
	int i=0;
	if(list == NULL)
		return;
	PrintRecords(list->left);
	printf("%s",list->name);
	for(i=0;i<30-strlen(list->name);i++) printf(" ");
	printf("%s",list->MobNo);
	for(i=0;i<20-strlen(list->MobNo);i++) printf(" ");
	printf("%s",list->Address);
	for(i=0;i<80-strlen(list->Address);i++) printf(" ");
	printf("%s",list->LastUse);
	printf(BLU"\n<--------------------->\n"RESET);
	PrintRecords(list->right);
}

//Function to insert a node in bst tree based on the mobile number of the customer
//This function takes 2 arguments: root of the BST and a BST node containing the credentials of the customer
//This function returns the root of the BST
BST* insert(BST *head,BST *temp){
	if(head==NULL)
		return temp;
	else if(strcmp(temp->MobNo,head->MobNo)<=0)
		head->left=insert(head->left,temp);
	else
		head->right=insert(head->right,temp);
return head;
}

//Function to convert integer date to a string
//This function takes 4 arguments: a2 as day, b2 as month and c2 as year, st is a string which will store the date.
void convert(int a2, int b2, int c2, char st[]){
	int i=0;
	if(a2<10){				//This segment stores the day of the date in the string st.
		st[i]=0+'0';
		st[++i]=a2+'0';
		st[++i]='/';
		i++;
	}
	else{
		st[i+1]=a2%10+'0';
		st[i]=a2/10+'0';
		i+=2;
		st[i++]='/';
	}
	if(b2<10){				//This segment stores the month of the date in the string st.
		st[i]=0+'0';
		st[++i]=b2+'0';
		st[++i]='/';
		i++;
	}
	else{
		st[i+1]=b2%10+'0';
		st[i]=b2/10+'0';
		i+=2;
		st[i++]='/';
	}
	st[i+3]=c2%10+'0'; c2=c2/10;		//This segment stores the year of the date in the string st.
	st[i+2]=c2%10+'0'; c2=c2/10;
	st[i+1]=c2%10+'0'; c2=c2/10;
	st[i]=c2+'0';

	i+=4;
	st[i]='\0';				//Finally terminating the string.

}

//Function to add new Record in File and bst tree
//This function takes two arguments: root of BST and root of trie data structure.
//It performs the following tasks:
//	->Opens the file Records.txt and then takes the credentials of the customer from the user as input
//	->Then it generates the current date using unistd.h and time.h libraries.
//	->Then it inserts the user details in the BST by calling the function: insert()
//	->While taking input from the user it simultaneously appends the user details in the file Records.txt.
//	->This function also inserts the customer's name into the TRIE by calling function insertTrie()
void AddRecords(BST *head, TRIE *trie){
	char str[100],st[14];
	BST *temp = (BST*)malloc(sizeof(BST));		//Dynamically declairing a BST node to hold the customer details.
	temp->left=temp->right=NULL;
	FILE *record = fopen("Records.txt","a");	//opening file Records.txt

	printf("Enter customer's name - ");
	scanf(" %[^\n]s",str);
	insertTrie(trie,str);				//inserting the customer's name into the TRIE.
	strcpy(temp->name,str);
	fprintf(record,"%s!",str);			//appending the customer's name to the Records.txt.

	printf("Enter customer's Mobile no. - +917971-");
	scanf(" %[^\n]s",str); strcpy(st,"+917971");
	strcat(st,str);
	strcpy(temp->MobNo,st);
	fprintf(record,"%s!",st);			//appending the customer's mobile number to the Records.txt.

	printf("Enter customer's Address - ");
	scanf(" %[^\n]s",str);
	strcpy(temp->Address,str);
	fprintf(record,"%s!",str);			//appending the customer's address to the Records.txt.

	time_t t = time(NULL);				//generating current date.
      	struct tm tm = *localtime(&t);
      	int a2=tm.tm_mday;				//generating current day.
      	int b2=tm.tm_mon + 1;				//generating current month.
      	int c2=tm.tm_year + 1900;			//generating current year.

      	convert(a2,b2,c2,st);				//storing the current date in the string st.
      	strcpy(temp->LastUse,st);
	fprintf(record,"%s!\n",st);			//appending the last used date in the Records.txt file.
	fclose(record);					//closing the file.

	head = insert(head,temp);			//inserting the customer details in the BST using insert function.
	co++;
}

//This function inserts the details of the customer in the BST and the name of the customer in TRIE
//This function takes 3 arguments:Node of BST, string containing customer details, root of TRIE.
//It splits str based on '!' and then accordingly inserts the name in the TRIE and all the details in the BST node,i.e.,list.
void InsertData(BST *list, char *str, TRIE *trie){
	int i=0,j=0;

	while(str[i]!='!'){		//Extracting customer's name from str and storing in list->name[i]
		list->name[i] = str[i];
		i++;
	}
	list->name[i]=='\0';
	insertTrie(trie,list->name);	//Inserting customer's name in TRIE using insertTrie function
	i++;

	while(str[i]!='!'){		//Extracting customer's mobile number from str and storing in list->MobNo[j]
		list->MobNo[j] = str[i];
		i++; j++;
	}
	list->MobNo[j] = '\0'; j=0;
	i++;

	while(str[i]!='!'){		//Extracting customer's address from str and storing in list->Address[j]
		list->Address[j] = str[i];
		j++; i++;
	}
	list->Address[j] = '\0';j=0;
	i++;

	while(str[i]!='!'){		//Extracting customer's last used date from str and storing in list->LastUse[j]
		list->LastUse[j] = str[i];
		j++; i++;
	}
	list->LastUse[j] = '\0';
}
//Inserting all the records in Records.txt to the BST
//This function calls two sub-functions:InsertData and insert
//It scans each line from Records.txt and then calls insertData function which carries data insertion part in the TRIE and also in a BST node temp.
//It then calls insert function which inserts temp into the BST.
BST *Records(BST *list,TRIE *trie){
	FILE *record = fopen("Records.txt","r");

	char str[500];

	while(fscanf(record," %[^\n]s",str)>=0){
		co++;
		BST *temp = (BST*)malloc(sizeof(BST));
		InsertData(temp,str,trie);

		temp->left = temp->right = NULL;

		list = insert(list,temp);
		}
	fclose(record);
return list;
}

//FindPhoneNumber function does the following tasks:
//checks whether a given phone number is there in the database.i.e, in the BST or not.
//returns 1 if the phone number is not in the database and 0 otherwise
int FindPhoneNumber(BST *root, char *phoneNumber,int check)
{
	if(root==NULL)
	{
		return check;
	}
	else if(strcmp(root->MobNo,phoneNumber)==0)
	{
	    int i=0;
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
			check=FindPhoneNumber(root->left,phoneNumber,check);
		if(root->right!=NULL)
			check=FindPhoneNumber(root->right,phoneNumber,check);
	}
	return check;
}
//------------------------------------------------------------------
//isChar function does the following tasks:
//checks whether there is any character in the mobile number or not
//returns 1 if there is any character in the mobile number and 0 otherwise
int isChar(char a[])
{
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]-48<0 || a[i]-48>9)
        {
            if(a[0]!=43)
            return 1;
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
    if((strlen(number)==13 && isChar(number)!=1))
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
   for(i=y1;i<y2;i++)
    {
          if(i%4==0)
              count+=366;
          else
            count+=365;
   }
   count-=month(m1,y1,mon);
   count-=d1;
   count+=month(m2,y2,mon);
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
      a1=(dateLast[0]-'0')*10+(dateLast[1]-'0');
      b1=(dateLast[3]-'0')*10+(dateLast[4]-'0');
      c1=(dateLast[6]-'0')*1000+(dateLast[7]-'0')*100+(dateLast[8]-'0')*10+(dateLast[9]-'0');


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
          //  printf("%d\n",daysB);
            list->Datediff=daysB;
            //printf("%d %d",daysB,list->Datediff);
              return 1;
          }

          else
            return 0;

}
/*This function sends the message to the defaulter about recharge and also sends some offer*/
void printMessage(BST *list){
  printf("\n");
    printf(YEL"\t_____________________________________________________________________\n");
    printf("\t|"RESET KRED"DEAR %s"RESET,list->name);
    for(int x=0;x<63-strlen(list->name);x++)
      printf(" ");
      printf(""YEL"|\n"RESET);
    printf(YEL"\t|"RESET"                                                                  "YEL"  |\n"RESET);
    printf(YEL"\t|"RESET"\tUR no"GRN" %s"RESET" hasnot been recharged  after"GRN" %s"RESET"  "YEL"   |\n"RESET,list->MobNo,list->LastUse);
    printf(YEL"\t|"RESET"\tPlease recharge with-in  %d  days to avail your number      "YEL" |\n"RESET,90-list->Datediff);
    printf(YEL"\t|"RESET"\tAfter %d days your number will be de-activated              "YEL" |\n   "RESET,90-list->Datediff);
    printf(YEL"\t|____________________________________________________________________|\n\n\n\n"RESET);

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
      if(check_date(list)){
				printf("%s::\n",list->name);
				printMessage(list);
			}

    //printf("LastUse:: %s\n",list->LastUse);
      getDate(list->left);
      getDate(list->right);
	}
  }
//month1 function returns the number of days in the month a
int month1(int a,int yy){
  int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
 int x=0,c;
 for(c=0;c<a-1;c++)
   {
  if(c==1)
     {
     if(yy%4==0)
     x+=29;
     else
     x+=28;
     }
   else
   x+=mon[c];
   }
 return x;
 }
  //The days1 function returns the number of days between the two dates d1/m1/y1 and d2/m2/y2
int days1(int d1,int d2,int m1,int m2,int y1,int y2){

  int count=0,i;
  for(i=y1;i<y2;i++)
    {
    if(i%4==0)
    count+=366;
    else
    count+=365;
    }
  count-=month1(m1,y1);
  count-=d1;
  count+=month1(m2,y2);
  count+=d2;
  if(count<0)
  count=count*-1;
  return count;
  }
	//Just to print the last node of tree
//traverse function returns the address of the last node of the tree and makes its parents link with it NULL
BST* traverse(BST *root,BST *parent){
    if(root==NULL){
			printf("Root null\n");
      exit(-1);
    }
    if(root->right!=NULL){
      traverse(root->right,root);
    }
    else if(root->left!=NULL){
      traverse(root->left,root);
    }
   else if(root->right==NULL && root->left==NULL){
			if(root==parent->left){
				parent->left=NULL;
			}
			else if(root==parent->right){
				parent->right=NULL;
			}
      return root;
    }
  }
	//The overwrite function overwrites the node to be deleted with the last node of binary search tree and adds the deleted node to the file deleteHistory.txt
void overwrite(BST *node,BST *new){
    FILE *fp = fopen("deleteHistory.txt","a+");
    fprintf(fp,"%s!%s!%s!%s!\n",node->name,node->MobNo,node->Address,node->LastUse);
    fclose(fp);
    strcpy(node->name,new->name);
    strcpy(node->MobNo,new->MobNo);
    strcpy(node->Address,new->Address);
    strcpy(node->LastUse,new->LastUse);

  }
//The deleteNode function calls the overwrite function and deletes the last node from the tree
void deleteNode(BST *root,BST *node){

		BST *new;
		new=traverse(root,root);
		//printf("$$$$%s  %s$$$\n",node->name,node->LastUse);
    overwrite(node,new);
		//printf("$$$%s  %s@@@\n",node->name,node->LastUse);
    free(new);

  }
	//The deleteNodeIfTrue function checks if the LastUse date was 3 months or before.If true then it calls delete function to delete that node
int deleteNodeIfTrue(BST *root,BST *node){
    char last[10];
    int d1,d2,m1,m2,y1,y2;
    strcpy(last,node->LastUse);
    d1=(last[0]-'0')*10+(last[1]-'0');
    m1=(last[3]-'0')*10+(last[4]-'0');
    y1=(last[6]-'0')*1000+(last[7]-'0')*100+(last[8]-'0')*10+(last[9]-'0');
		//printf("%d %d %d\n",d1,m1,y1);
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		d2=tm.tm_mday;
		m2=tm.tm_mon + 1;
		y2=tm.tm_year + 1900;
		/*//Debug:
		printf("%d %d %d\n",d2,m2,y2);
		*/
    if(days1(d1,d2,m1,m2,y1,y2)>=90){
      deleteNode(root,node);
      return 1;
    }
  return 0;
  }

//The Preorder function travels to each node in preorder manner and calls the deleteNodeIfTrue function to check if the node has to be deleted
void preorder(BST *root,BST *head){
    if(root==NULL){
      exit(-1);
    }
    if(head!=NULL && head->left!=NULL){
      preorder(root,head->left);
    }
    if(head!=NULL){
	int flag=1;
	while(flag==1)		//printf("%s\n",head->name);
      flag = deleteNodeIfTrue(root,head);

    }
    if(head!=NULL && head->right!=NULL){
      preorder(root,head->right);
    }
  }
//The inorder function writes the tree again ,after updating,in the input file
void inorder(FILE *f,BST *root){
	if(root!=NULL){
		co++;
		fprintf(f,"%s!%s!%s!%s!\n",root->name,root->MobNo,root->Address,root->LastUse);
	}
	if(root!=NULL && root->left!=NULL){
		inorder(f,root->left);
	}
	if(root!=NULL && root->right!=NULL){
		inorder(f,root->right);
	}
}
//The delete() is supposed to be the main delete function which performs the overall delete task
void delete(BST *head){
    preorder(head,head);

		FILE *newrec=fopen("Records.txt","w+");
		inorder(newrec,head);
		fclose(newrec);
  }


//This function will perform search either on the basis of customer name or customer mobile number depending upon the user's input.
void SearchOption(BST *list, TRIE *trie){
		int option;
		printf("1. Search by Mobile number.\n2. Search by Name\n");
		scanf("%d",&option);
		switch(option){
			case 1:
				Search(list);
				break;
			case 2:
				Trie(list,trie);
				break;
			}
	}

void Start(BST *list, TRIE *trie){
	int ch,option='y',x;
	printf(CYN"___________________________________________________________________________________________________________________________________________________\n",RESET);

	printf(GRN"1."RESET" New Customer\n"GRN"2."RESET" Show Records\n"GRN"3."RESET" Search Records\n"GRN"4."RESET" Check DEFAULTER list\n"GRN"5."RESET" Delete DEFAULTERS\n"GRN"6."RESET" Exit\n");
	printf(CYN"___________________________________________________________________________________________________________________________________________________"RESET"\n");

	scanf("%d",&ch);
	system("clear");
	switch(ch){
		case 1:
			while(option=='y'||option=='Y'){
			AddRecords(list,trie);
			printf("\nDo you want to add another RECORD y/n?\n");
			getchar();
			scanf("%c",&option);
			}
			option = 'y';
			break;
		case 2:
			PrintRecords(list);
			printf(GRN"\n%d Records found.\n\n"RESET,co);
			break;
		case 3:
			while(option=='y'||option=='Y'){
			SearchOption(list,trie);
			printf("\nDo you want to SEARCH another record y/n?\n");
			getchar();
			scanf("%c",&option);
			}
			option = 'y';
			break;
		case 4:
			getDate(list);
			break;
		case 5:
			co=0;
			delete(list);

			printf("\nThe Defaulters list has been deleted.\n\n");
			break;
		case 6:
			return;
		default:
			printf("Please enter a correct option.\n");
			Start(list,trie);
	}
	Start(list, trie);
	//system("clear");
}


int main(){
	BST *list = (BST*)malloc(sizeof(BST));
	list = NULL;
	TRIE *trie = getNode();

	list = Records(list,trie);

	Start(list,trie);

return 0;
}
