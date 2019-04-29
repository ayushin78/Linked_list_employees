/******************************************************************************
 *     FILENAME       :	linked_list_utils.c
 *
 *     DESCRIPTION    :	This file defines the driver function required to call
 *				the utility functions for linked list Program.
 *                 
 *     AUTHOR         :	Ayushi Negi
 * 
 *
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <linked_list_utils.h>


/******************************************************************************
* FUNCTION NAME	:	myfflush
* DESCRIPTION		:	This function is a replacement of inbuilt function 
*				fflush(stdin)
* ARGUMENT		:	No parameters
* RETURNS		:	It returns void  		
* 
******************************************************************************/
void myfflush(void)
{
    while('\n' != getchar());
}



/******************************************************************************
* FUNCTION NAME	:	getIntegerInput
* DESCRIPTION		:	This function takes string input from user
* ARGUMENT		:	Self-descriptive
* RETURNS		:	SUCCESS, if successful else, FAILURE
*
******************************************************************************/
int getStringInput(char **inputString)
{
	int len = 0;
	char buff[MAX_SIZE];

	fgets(buff, MAX_SIZE-1, stdin);
	len = strlen(buff);

	if ('\n' == buff[len - 1])
    	{
        	buff[len - 1] = '\0';
    	}
    	else
	{
        	myfflush();
   	} 
    
	*inputString = (char *)calloc(strlen(buff) + 1, sizeof(char));
	
	if(NULL == *inputString)
	{	
		perror("Memory allocation failure");
		return FAILURE;
	}

	strcpy(*inputString, buff);

	return SUCCESS;
}



/******************************************************************************
* FUNCTION NAME	:	getIntegerInput
* DESCRIPTION		:	This function takes integer input from user
* ARGUMENT		:	Self-descriptive
* RETURNS		:	SUCCESS, if successful else, FAILURE
*
******************************************************************************/
void getIntegerInput(unsigned int *input)
{
	while(1)
	{
		if(!scanf("%u", input))
		{
			printf("Enter a valid integer value: ");
		}
		else
		{
			myfflush();
			break;
		}
		myfflush();
	}
}



/******************************************************************************
* FUNCTION NAME	:	isValidId
* DESCRIPTION		:	This function validates the employee Id
* ARGUMENT		:	Character pointer to the employee Id
* RETURNS		:	SUCCESS, If Id is valid else FAILURE  		
* 
******************************************************************************/
int isValidId(char *id)
{
	int i = 0;

	/* Validate length of id */
	if(strlen(id) != 5)
	{
		return FAILURE;
	}
	
	/* Validate the characters of id */
	while(id[i] != '\0')
	{
		if(!isdigit(id[i]))
		{
			return FAILURE;
		}

		i++;
	}	
	
	return SUCCESS;
}



/******************************************************************************
* FUNCTION NAME	:	isValidName
* DESCRIPTION		:	This function validates the employee name
* ARGUMENT		:	Character pointer to the employee Id
* RETURNS		:	SUCCESS, If Id is valid else FAILURE   		
* 
******************************************************************************/
int isValidName(char *name)
{
	int i = 0;
	
	/* Validate the characters of name */
	while(name[i] != '\0')
	{
		if((!isalpha(name[i])) && (name[i] != ' '))
		{
			return FAILURE;
		}

		i++;
	}	
	
	return SUCCESS;
}



/******************************************************************************
* FUNCTION NAME	:	getEmployeeId
* DESCRIPTION		:	This function takes employee Id from user as input 
*				till the user enters a valid employee Id
* ARGUMENT		:	Parameters are self-descriptive.
* RETURNS		:	SUCCESS, if successful else FAILURE   		
* 
******************************************************************************/
int getEmployeeId(char **inputString)
{
	while(SUCCESS == getStringInput(inputString))
	{
		/* If valid Id, return SUCCESS */
		if(isValidId(*inputString))
		{
			return SUCCESS;
		}
		else
		{
			FREE(*inputString);
			puts("Invalid Id! Please enter valid id");
		}
	}

	perror("Employee Id input error");
	return FAILURE;
}



/******************************************************************************
* FUNCTION NAME	:	getEmployeeName
* DESCRIPTION		:	This function takes employee name from user as 
* 				input till the user enters a valid employee name
* ARGUMENT		:	Parameters are self-descriptive.
* RETURNS		:	SUCCESS, if successful else FAILURE   		
* 
******************************************************************************/
int getEmployeeName(char **inputString)
{
	while(SUCCESS == getStringInput(inputString))
	{
		if(isValidName(*inputString))
		{
			return SUCCESS;
		}
		else
		{
			FREE(*inputString);
			puts("Invalid Name! Please enter valid name");
		}
	}

	perror("Employee name input error");
	return FAILURE;
}



/******************************************************************************
* FUNCTION NAME	:	inputEmployeeDetails
* DESCRIPTION		:	This function is used to input the employee details 
*				from user
* ARGUMENT		:	Double pointer to the employee
* RETURNS		:	SUCCESS, if successful else FAILURE   		
* 
******************************************************************************/
int inputEmployeeDetails(employee_t **emp)
{
	/* Create employee */
	*emp = (employee_t *)calloc(1, sizeof(employee_t));

	/* Check if memory allocation was successful */
	if(NULL == *emp)
	{
		perror("Memory allocation error");
		return FAILURE;
	}
	
	puts("Enter employee id");
	if(FAILURE == getEmployeeId(&((*emp)->id)))
	{
		FREE(*emp);
		return FAILURE;	
	}
		

	puts("Please enter employee name");
	if(FAILURE == getEmployeeName(&((*emp)->name)))
	{
		FREE(*emp);
		return FAILURE;
	}

	return SUCCESS;	
}



/******************************************************************************
* FUNCTION NAME	:	createNode
* DESCRIPTION		:	This function is used to create a new node
* ARGUMENT	 	:	Double pointer to the new node
* RETURNS		:	SUCCESS, if successful else FAILURE  
*
******************************************************************************/
int createNode(listNode **newNode)
{
	employee_t *emp = NULL;

	if(FAILURE == inputEmployeeDetails(&emp))	
	{
		return FAILURE;
	}

	/* Create a new list node */
	*newNode = (listNode *)calloc(1, sizeof(listNode));

	/* Check for memory allocation, if failure, return FAILURE */
	if(NULL == *newNode)
	{
		puts("Memory allocation error");
		return FAILURE;
	}

	(*newNode)->employee = emp; 
	(*newNode)->next = NULL;

	return SUCCESS;
}



/******************************************************************************
* FUNCTION NAME	:	sortedInsert
* DESCRIPTION		:	This function is used to insert a node in
*				sorted order of employee id
* ARGUMENT	 	:	Double pointer to the head of the list
* RETURNS         	:	SUCCESS, if successful else FAILURE  					   
*
******************************************************************************/
int sortedInsert(listNode **head)
{
	listNode *newNode = NULL;
	listNode *current = *head;
	listNode *prev = NULL;

	if(FAILURE == createNode(&newNode))
	{
		return FAILURE;	
	}
	
	/* If empty list, point head to newNode and return SUCCESS */
	if(NULL == *head)
	{
		*head = newNode;
		current = *head;
		return SUCCESS;
	}

	/* update current till current points to node having larger 
		value of id than id of newNode */
	while((current != NULL) && 
		(strcmp(newNode->employee->id, current->employee->id) > 0))
	{
		prev = current;
		current = current->next;
	}

	/* update newNode->next pointer to current */
	newNode->next = current;	
	
	/* prev is NULL, i.e. no node will have a higher id than newNode 
		node will be inserted at beginneing*/
	if(prev == NULL)
	{
		*head = newNode;
		return SUCCESS;
	}

	/* update next of prev to point to newNode */	
	prev->next = newNode;

	return SUCCESS;		
}



/******************************************************************************
* FUNCTION NAME	:	insertAtBeg
* DESCRIPTION		:	This function is used to insert a node to the 
*				beginning of the list
* ARGUMENT	 	:	Double pointer to the head of the list
* RETURNS         	:	SUCCESS, if successful else FAILURE  					   
*
******************************************************************************/
int insertAtBeg(listNode **head)
{
	listNode *newNode = NULL;

	if(FAILURE == createNode(&newNode))
	{
		return FAILURE;	
	}
	
	/* If empty list, point head to newNode and return SUCCESS */
	if(NULL == *head)
	{
		*head = newNode;
		return SUCCESS;
	}

	newNode -> next = *head;
	*head = newNode;

	return SUCCESS;		
}



/******************************************************************************
* FUNCTION NAME	:	insertEmployees
* DESCRIPTION		:	This function takes number of employees from user 
*				and inserts the employees data in the list
* ARGUMENT		:	head pointer to the list
* RETURNS		:	SUCCESS, if successful else FAILURE   		
* 
******************************************************************************/
int insertEmployees(listNode **head)
{
	unsigned int num = 0;
	puts("Enter number of employees to be added \n");
	getIntegerInput(&num);

	while(num > 0)
	{
		if(FAILURE == sortedInsert(head))
		{
			puts("Employee insertion failed");				
		}
		else
		{
			num--;
		}
	}
	
	return SUCCESS;
}



/******************************************************************************
* FUNCTION NAME	:	displayEmployee
* DESCRIPTION		:	This function displays the details of an employee
* ARGUMENT		:	pointer to the node that needs to be displayed
* RETURNS		:	Nothing
*					  
******************************************************************************/
void displayEmployee(listNode *current)
{
	if(NULL != current)
	{
		printf("Employee Id : %s\n", current->employee->id);
		printf("Employee Name : %s\n", current->employee->name);
	}
}



/******************************************************************************
* FUNCTION NAME	:   displayList
* DESCRIPTION		:   This function displays the complete list
* ARGUMENT		:   pointer to head of the list
* RETURNS		:   Nothing
*					  
******************************************************************************/
void displayList(listNode *head)
{
	if(NULL == head)
	{
		printf("\n---Empty list---\n");
	}
	else
	{
		printf("\n---LIST OF EMPLOYEES---\n");
	}
	while(NULL != head)
	{
		displayEmployee(head);
		head = head->next;
	}
}



/******************************************************************************
* FUNCTION NAME	:	deleteNode
* DESCRIPTION		:	This function deletes the node present at a given 
*				position in the list
* ARGUMENTS		:	Double pointer to the head node of the list
* RETURNS		:	SUCCESS, if successful else FAILURE 
*
******************************************************************************/
int deleteNode(listNode **head)
{
	unsigned int m = -1;
	listNode *current = *head;
	listNode *prev = NULL;

	if(NULL == current)
	{
		puts("Empty list, deletion can not be done");
		return FAILURE;	
	}
	
	puts("Enter position");
	getIntegerInput(&m);

	/* Update current to mth position */
	while((NULL != current->next) && (m > 1))
	{
		prev = current;
		current = current->next;
		m--;			
	}
	
	/* Check if m is greater than the length of the list */ 
	if(m > 1)
	{
		printf("Invalid number/position, please choose a smaller number \n");
		return FAILURE;
	}

	/* If first node is to be deleted */
	if(NULL == prev)
	{
		*head = current->next; 
	}
	else
	{
		prev->next = current->next;
	}

	/* free memory allocated for the node to be deleted */
	freeNode(current);

	return SUCCESS;
}



/******************************************************************************
* FUNCTION NAME	:	searchByEmployeeName
* DESCRIPTION		:	This function searches the list by employee name
* ARGUMENT		:	Head pointer to list
* RETURNS		:	SUCCESS, if employee is found successfully 
*				else, Failure 
*
******************************************************************************/
int searchByEmployeeName(listNode *head)
{
	listNode *current = head;
	char searchName[MAX_SIZE];
	
	printf("Please enter employee name for search : ");	

	fgets(searchName, MAX_SIZE, stdin);	
	searchName[strlen(searchName) - 1] = '\0';
	
	while(NULL != current)
	{
		if(0 == strcmp(current->employee->name, searchName))
		{
			puts("Employee found! Details are given below :- ");
			displayEmployee(current);
			return SUCCESS;
		}
		current = current->next;
	}

	puts("Sorry! No employee found for this name");
	return FAILURE;
}



/******************************************************************************
* FUNCTION NAME	:	playMagicGame
* DESCRIPTION		:	This function gets a magic number from the 
*				user repeatedly, deletes the node present 
*				at that number and finally displays the
*				winner employee 
* ARGUMENT		:	Double pointer to the head of the list
* RETURNS		:	Nothing   		
* 
******************************************************************************/
void playMagicGame(listNode **head)
{
	printf("\nGame starts...\n");
	
	while(NULL != (*head)->next)
	{
		deleteNode(head);
	}
	
	printf("The lucky winner is : \n");
	displayEmployee(*head);
}



/******************************************************************************
* FUNCTION NAME	:	sortedMerge
* DESCRIPTION		:	This function merges two lists in sorted manner
*				by name
* ARGUMENT		:	head pointers of both lists
* RETURNS		:	head pointer to the newly formed list   		
* 
******************************************************************************/
listNode* sortedMerge(listNode *a, listNode *b)
{
	listNode *head = NULL;
	
	if(a == NULL)
	{
		return b;
	}

	if(b == NULL)
	{
		return a;
	}


	if(strcmp(a->employee->name, b->employee->name) <= 0)
	{
		head = a;
		head->next = sortedMerge(a->next, b);	
	}
	else
	{
		head = b;
		head->next = sortedMerge(b->next, a);
	}
		
	return head;
}



/******************************************************************************
* FUNCTION NAME	:	getMidNode
* DESCRIPTION		:	This function finds the midpoint of the list
* ARGUMENT		:	POinter to head of the list
* RETURNS		:	If list is of even length, it returns pointer to
*				(length / 2 + 1)th Node, else (length/2)th Node
*
******************************************************************************/
void splitAtMid(listNode *head, listNode **a, listNode **b)
{

	listNode *slow = head;
	listNode *fast = head;
	listNode *prev = NULL;

	/* slow will beth mid point of the list 
	   and prev will be its previous node */
	while((fast != NULL) && (fast->next != NULL))
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	/* a will be the head of the first half */
	*a = head;

	/* b will be the head of the other half of the list */
	*b = slow;

	/* To split the list in half */
	if(prev != NULL)
	{
		prev->next = NULL;
	}

}



/******************************************************************************
* FUNCTION NAME	:	sort
* DESCRIPTION		:	This function sorts the list by employee id
* ARGUMENT		:	head pointer to the list
* RETURNS		:	new head pointer to the list	
* 
******************************************************************************/
void sort(listNode **head)
{
	/* Base Case */
	if((*head == NULL) || ((*head)->next == NULL))
	{
		return ;
	}
	
	listNode *a = NULL;
	listNode *b = NULL;

	splitAtMid(*head, &a, &b);
	sort(&a);
	sort(&b);

	*head = sortedMerge(a, b);
}



/******************************************************************************
* FUNCTION NAME	:	freeList
* DESCRIPTION		:	This function deallocates the memory used by the 
*				list
* ARGUMENT		:	Double pointer to the head of the list
* RETURNS		:	Nothing   		
* 
******************************************************************************/
void freeList(listNode *head)
{
	while(NULL != head)
	{
		listNode *nextNode = head->next;
		freeNode(head);
		head = nextNode;
	}
}



/******************************************************************************
* FUNCTION NAME	:	freeNode
* DESCRIPTION		:	This function deallocates the memory used by the 
*				given node
* ARGUMENT		:	Pointer to node that needs to be deallocated
* RETURNS		:	Nothing		
* 
******************************************************************************/
void freeNode(listNode *ptr)
{
	FREE(ptr->employee->id);
	FREE(ptr->employee->name);
	FREE(ptr->employee);
	FREE(ptr);
}
