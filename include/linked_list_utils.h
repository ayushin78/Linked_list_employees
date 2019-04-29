/*******************************************************************************
 *	FILENAME       :    linked_list_utils.h
 *
 *	DESCRIPTION    :    This file is the header file and contains all the 
 * 				required declarations and macros.
 *                 
 *	AUTHOR         :    Ayushi Negi
 * 
 *	Copyright © 2018 Aricent  Group  All Rights Reserved
 *
********************************************************************************/

#ifndef __LINKED_LIST_UTILS_H
#define __LINKED_LIST_UTILS_H

/****************************************************************************
 * 			  MACRO DEFINITONS
 ****************************************************************************/
#define SUCCESS 1
#define FAILURE 0

#define MAX_SIZE 255

#define ADD_EMPLOYEES 0
#define DELETE_EMPLOYEE 1
#define SEARCH_EMPLOYEE 2
#define PLAY_MAGIC_GAME 3
#define SORT_BY_NAME 4
#define EXIT 5 


/* Macro function to free the allocated memory */
#define FREE(str){ \
	if(str != NULL){ \
		free(str); \
		str = NULL; \
	} \
}

/* Macro function to check for the memory allocation errors. */
#define CHECK_MEMORY_ERRORS(ptr){ \
	if(ptr == NULL){ \
		puts("Error : Memory Allocation Failure"); \
		exit(FAILURE); \
	} \
} 


/****************************************************************************
 * 			  STRUCT DEFINITONS
 ****************************************************************************/

	typedef struct employee{
		char *id;
		char *name;
	} employee_t;


	typedef struct listNode{
		employee_t *employee;
		struct listNode *next;
	} listNode;


/************************************************************************
 *				FUNCTION PROTOTYPES
 ***********************************************************************/
	void myfflush(void);	
	int getStringInput(char **inputString);
	void getIntegerInput(unsigned int *input);
	int createNode(listNode **newNode);
	int insertAtBeg(listNode **head);
	int sortedInsert(listNode **head);
	int insertEmployees(listNode **head);
	int isValidId(char *id);
	int isValidName(char *name);
	int getEmployeeId(char **id);
	int getEmployeeName(char **name);
	int searchByEmployeeName(listNode *head);
	int inputEmployeeDetails(employee_t **emp);
	int deleteNode(listNode **head);
	void displayEmployee(listNode *current);
	void displayList(listNode *head);
	void playMagicGame(listNode **head);
	void freeList(listNode *head);
	void freeNode(listNode *ptr);
	void splitAtMid(listNode *head, listNode **a, listNode **b);
	listNode* sortedMerge(listNode *a, listNode *b);
	void sort(listNode **head);

	
#endif
