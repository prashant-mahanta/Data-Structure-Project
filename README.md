## Data-Structure-Project

Team Members:

  Name                         Roll              E-mail
  
1.Chandrajeet Choudhary      201601017         chandrajeet.c16@iiits.in

2.Wasim Ishaq Khan           201601107         wasim.i16@iiits.in

3.Kaustubh Pandey            201601041         kaustubh.p16@iiits.in

4.Prashant Kumar Mahanta     201601066         prashantkumar.m16@iiits.in

5. Prashant Mahanta          S20160010066      prashantkumar.m23@gmail.com

Overview:
For our project we chose Binary Search Tree(BST) as our data structure as the main focus of our project
was on searching records and BST has average time complexity O(log n) and worst case O(n) for search, delete
and insert operations. For searching records we have also used Trie data structure to search by name.

-----------------------------------------------------------------------------------

The MAIN function:
  The main function automatically calls the --Records()-- function each time on startup which inserts the data
  in a Binary Search Tree from our database file "Records.txt" which consists of existing records.
  Then the --Start()-- function is called which provides the following options:
  Enter the number to execute the function
      Function                  Description
  1-  AddRecords()            To add new record
  2-  PrintRecords()          To print all the existing records
  3-  Search()                To search records
  4-  delete()                To delete defaulter records
  5-  getDate()               To generate defaulter automatic message

  *************************************************************************************************************************************************************************************
                                              Detailed Description
  Functions:
  ## 1) void AddRecords(BST *head, TRIE *trie)-
  
	         1.1. Defining a BST tree structure with 5 fields

	         1.2. Defining a trie structure

	         1.3.void PrintDetails(BST *head,char str[]): Function to print all the records.i.e., the elements of the BST in INORDER traversal using PrintRecords function. This function takes the root of
	            the BST as its argument.
	         1.4. insert()
            BST* insert(BST *head,BST *temp)
                        function which inserts a node in the BST based on the mobile number of the customer
		                  ->This function takes 2 arguments: root of the BST and a BST node containing the credentials of the customer
		                   ->This function returns the root of the BST

	         1.5. convert()
                  void convert(int a2, int b2, int c2, char st[])
                      Function which converts an integer date to a string.
		                  ->This function takes 4 arguments: a2 as day, b2 as month and c2 as year, st is a string which will store the date.

	         1.6. AddRecords() function to add new Record in File and BST tree
		                    ->This function takes two arguments: root of BST and root of trie data structure.
		                    ->It performs the following tasks:
			                           ->Opens the file Records.txt and then takes the credentials of the customer from the user as input
			                           ->Then it generates the current date using unistd.h and time.h libraries.
			                           ->Then it inserts the user details in the BST by calling the function: insert()
			                           ->While taking input from the user it simultaneously appends the user details in the file Records.txt.
			                           ->This function also inserts the customer's name into the TRIE by calling function insertTrie()

	         1.7. PrintDetails() function which does the following task:
		                    ->For each name whose prefix is the prefix entered by the user, this fuction prints all the details corresponding to that name.

	         1.8. InsertData()function:
                  void InsertData(BST *list, char *str, TRIE *trie)
                                  This function inserts the details of the customer in the BST and the name of the customer in TRIE
				                              This function takes 3 arguments:Node of BST, string containing customer details, root of TRIE.
				                                  It splits str based on '!' and then accordingly inserts the name in the TRIE and all the details in the BST node,i.e.,list.

	         1.9. Inserting all the records in Records.txt to the BST using Records() function
			                               This function calls two sub-functions:insertData and insert
			                                It scans each line from Records.txt and then calls insertData function which carries data insertion part in the TRIE and also in a BST node temp.
			                                   It then calls insert function which inserts temp into the BST.


## 2) void PrintRecords(BST *list)-

		To print all the records stored in Binary Search Tree. It accepts the head of BST as input and performs inorder traversal to print the tree.

  -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
## 3) Search()-

          This function provides two options-(1)To search on the basis of mobile number (2)To search on the basis of name
    (1)   ->SEARCHING WHETHER A MOBILE NUMBER IS THERE IN THE DATABASE(BST) OR NOT:
    3.1.void Search(BST *list)
    3.1.1. int checkValidity(char number[]):
          Taking an input from the user and checking whether that input is a valid mobile number or not by calling a function checkValidity which internally calls another function isChar.
	         ->checkValidity function returns 1 if the mobile number is an invalid number and 0 otherwise.
	          ->If the mobile number is an invalid number then it prompts the user 2 times to enter a valid mobile number.
	           ->If the user enters an invalid mobile number 3 times then he can't access the database.
	            ->If the mobile number entered by the user is a valid one then we call a function Search.
    3.1.2. Search function performs the following tasks:
	           ->checks whether the mobile number is there in the database or not.
	            ->If it is there in the database then it prints the details of the customer corresponding to that mobile number.



## (2) PRINTING ALL THE NAMES BEGINING WITH A PREFIX:

        SEARCHING ALL THE NAMES BEGINING WITH A PARTICULAR PREFIX AND THEN SUBSEQUENTLY PRINTING THEM USING TRIE DATA STRUCTURE.
3.2.  void Trie(BST *list, TRIE *trie)
	3.2.1. Creating a trie data structure with two fields:
      		  ->A pointer to an array of 53 character pointers.
      		  ->A boolean flag IsLeaf depicting whether the end of a word in the trie is reached or not.

	3.2.2. TRIE *getNode()
          Creating A function getNode which performs the following task:
    		->Dynamically allocates space to a trie node
    		->checks if the space allocation was successfull or not
    		->If the allocation was successfull:
    			->initialising all the character pointers of the character pointer array as null
    		->returns the head of the trie

	3.2.3. int C2I(char ch)
          A function C2I which does the following tasks:
        		->Converts a character to an integer by converting:
        		->lower-case alphabets to integers in the inclusive range of 0-25
        		->space to 26
        		->upper-case alphabets to integers in the inclusive range of 27-53

	3.2.4. void insertTrie(TRIE *root, const char *key)
                Inserting a node into the trie data structure using the insertTrie function which performs the following task:
		            ->inserts a name to the trie data structure

	3.2.5. Taking an input from the user which serves as our prefix, corresponding to which we have to print all the names to which that prefix is common.
            		->Firstly we call a function search which searches whether that prefix is there in the trie data structure or not
            		->If it is there in the trie data structure then we call another function.i.e.,t.

	3.2.6. Function t performs the following tasks:
		            ->For each name whose prefix is the prefix entered by the user, it calls a function PrintDetails which prints all the details of that name.
			    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## 4)  void getDate(BST *list)-

The function ____getDate():
 Checks who all are in the defaulter's(didn't used from last two months) list :
  ->In this function we have to go to each note of the BST and
  ->check the date between present date and last used date by the function ___check_date():

      4.1. int check_date(BST *list)
                  ->check_date calculates number of days between Last Use date and present Date
                  ->This function calls function ___days() to calculate number of days between Last Use and Present Days

      4.2. int days(int y1,int y2,int m1,int m2,int d1,int d2)
                        This function calculates the number of days between two dates. Say the date D1 is older than D2.
                        Then we initially take all the days of the year in D1 and add all the days of the years in between.
                        We have till now not added the number of days in the year of D2. Now we subtract the extra days added
                        (When we took all days of year(D1)) and add the left over days of D2.
                        Both of these are done using function ____month()

                        ->This function accepts the month and year as input and returns the total number of days starting
                        from January till the end of that month .And returns the number of days

      4.3.  void printMessage(BST *list)
                                    ->function check_date returns
                                    1 : if the difference between present and last used date is 60 to 90 days
                                            ->then call printMessage function to send SMS and Offer to the customer
                                    0 : else
				    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

5) delete()-

Sub-Functions:
*********************
5.1. month()
5.2. days()
5.3. traverse()
5.4. overwrite()
5.5. deleteNode()
5.6. deleteNodeIfTrue()
5.7. preorder()
5.8. inorder()
5.9. delete()
**********************
Description:
__________________________________________________________________________________________________
__________________________________________________________________________________________________

### 5.1. int month(int months,int year):

                This function accepts the month and year as input and returns the total number of
                days starting from January till the end of that month.Case of leap year is also
                checked.The number of days of each of the month is stored in an array. The days
                are added till the input month and returned.
		
-------------------------------------------------------------------------------------------------------

### 5.2. int days(int d1,int d2,int m1,int m2,int y1,int y2):

          This function calculates the number of days betweentwo dates. Say the date D1 is older than D2.
          Then we initially take all the days of the year in D1 and add all the days of the years in between.
          We have till now not added the number of days in the year of D2. Now we subtract the extra days added
          (When we took all days of year(D1)) and add the left over days of D2.
          Both of these are done using --month()--function
	  
___________________________________________________________________________________________________________
___________________________________________________________________________________________________________

### 5.3. BST* traverse(BST *root,BST *parent):

        This function takes two args- root and parent, both of which are initially the same. root changes each
        time in recursive call and acts like current node.The parent is always the parent of the current node
        Finally, this function returns the address of the LAST NODE of the binary search tree.
        At the same time its address in the parent is made NULL
	
--------------------------------------------------------------------------------------------------------------

### 5.4. void overwrite(BST *node,BST *new):

      This function accepts two nodes- node and new and overwrites the data of new in node
      
--------------------------------------------------------------------------------------------------------------

### 5.5. void deleteNode(BST *root,BST *node):

          This function uses the traverse and overwrite function to delete a node from a Binary Search Tree.
          It performs the following:
          ->Find the last node of tree
          ->Overwrite the node to be deleted with the last node
          ->free the last node
	  
_____________________________________________________________________________________________________________
_____________________________________________________________________________________________________________

### 5.6. void deleteNodeIfTrue(BST *root,BST *node):

          This function performs in the following way:
          ->Calculate the difference b/w LastUse and currdate by calling --days()--function
            ->If difference>=90 days(3 months)
              **DELETE THE NODE BY --deleteNode()-- function
	      
_____________________________________________________________________________________________________________
_____________________________________________________________________________________________________________

### 5.7. void preorder(BST *root,BST *head):

            This function simply performs the preorder traversal(left,root,right) of tree and calls the
            --deleteNodeIfTrue()--function to check if the node has to be deleted or not
	    
_______________________________________________________________________________________________________________
_______________________________________________________________________________________________________________

### 5.8. void inorder(FILE *f,BST *root):

            This function accepts the records file address and root of BinarySearchTree and rewrites the whole data of
            tree into the records file. The traversal is done in inorder fashion.
	    
_______________________________________________________________________________________________________________


### 5.9. void delete(BST *head):

            This is the main delete function.
            ->Calls the --preorder()-- function to perform the delete task.
            ->Writes the deleted records in a new file delete history.
            ->Calls --inorder()-- function to update the records file.


----------------------------------------------------------------------------------------------------------------------------------------

This project was done for Datastructure course in the 2nd Semester of B.Tech at IIIT Sri City.