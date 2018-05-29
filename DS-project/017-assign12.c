#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include "107-assign12.c"
#define Size (53)
#define KRED  "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
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

//----------------------------------------------------------------------------------------------------------
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
	TRIE *cnode = (TRIE*)malloc(sizeof(TRIE)); 	//dynamically allocating space to a trie node
	if(cnode){					//checking if the space has been allocated to the trie node(cnode) or not
		int i;
		cnode->IsLeaf = false;
		for(i=0;i<Size;i++)			//initialising all the character pointers of the character pointer array as null
			cnode->child[i]=NULL;
		}
	return cnode;					//returning the head of the trie
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

//Function to do different tasks
void Start(BST *list, TRIE *trie){
	int ch,option='y',x;
	printf("1. New Customer\n2. Show Records\n3. Search Records\n4. Check DEFAULTER list\n5. Delete DEFAULTERS\n6. Exit\n");
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
			printf("%d Records found.\n\n",co);
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
		/*case 4:
			getDate(list);
			break;
		case 5:
			co=0;
			delete(list);
			
			printf("\nThe Defaulters list has been deleted.\n\n"); 
			break;*/
		case 6:
			return;
		default:
			printf("Please enter a correct option.\n");
			Start(list,trie);
	}
	Start(list, trie);
	//system("clear");
}
//----------------------------------------------------------------------------------------------------------
int main(){
	BST *list = (BST*)malloc(sizeof(BST));
	list = NULL;
	TRIE *trie = getNode();

	list = Records(list,trie);

	Start(list,trie);

return 0;
}
