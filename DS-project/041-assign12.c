#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include "017-assign12.c"
#define Size (53)
#define KRED  "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

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
  /*DEBUG:
  printf("The no. of days1 b/w the 2 dates = %d days1",count);*/
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
			/*DEBUG:
			if(k==0){
				printf("#%s right  %s\n",root->right->name,parent->name);
			}*/
      traverse(root->right,root);
    }
    else if(root->left!=NULL){
			/*DEBUG:
			if(k==0){
				printf("#%s left  %s\n",root->left->name,parent->name);
			}*/
      traverse(root->left,root);
    }
   else if(root->right==NULL && root->left==NULL){
			/*DEBUG:
			printf("%s ***\n",root->name);*/
			//BST *p=root;

			if(root==parent->left){
				parent->left=NULL;
			}
			else if(root==parent->right){
				parent->right=NULL;
			}
			//pre(root);
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

  //  node->Datediff=new->Datediff;
  }


//The deleteNode function calls the overwrite function and deletes the last node from the tree
void deleteNode(BST *root,BST *node){

		BST *new;

		new=traverse(root,root);
		//DEBUG:printf("$$$$%s  %s$$$\n",node->name,node->LastUse);
    overwrite(node,new);
		//DEBUG:printf("$$$%s  %s@@@\n",node->name,node->LastUse);
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
    //DEBUG:
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
			//printf("YES\n");
			//pre(root);
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
	void Start2(BST *list, TRIE *trie){
		int ch,option='y',x;
		printf("1. New Customer\n2. Show Records\n4. Delete DEFAULTERS\n6. Exit\n");
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

			case 4:
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
		Start2(list, trie);
		//system("clear");
	}
/*int main(){
	BST *list = (BST*)malloc(sizeof(BST));
	list = NULL;
	TRIE *trie = getNode();

	list = Records(list,trie);

	Start2(list,trie);
}*/
