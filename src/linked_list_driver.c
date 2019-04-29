/*******************************************************************************
 *	FILENAME       :	linked_list_driver.c
 *
 *	DESCRIPTION    :	This file defines the driver function required to 
 *				call the utility functions for linked_list.
 *                 
 *	AUTHOR         :	Ayushi Negi
 * 
 *
********************************************************************************/

#include <stdio.h>
#include <linked_list_utils.h>

/*
 * Driver function for linked list operations
 *
*/
int main()
{
	listNode *head = NULL;
	int another = 1;
	unsigned choice = -1;	

	while(another)
	{
		printf("\n Enter \n" 
			"0 : to add an employee \n"
			"1 : to delete mth employee \n"
			"2 : to search an employee \n" 
			"3 : to play magic game \n"
			"4 : to sort by employee name \n"
		        "5 : to EXIT \n");

		printf("Enter choice \n");
		getIntegerInput(&choice);
	
		switch(choice)
		{
			case ADD_EMPLOYEES:
				insertEmployees(&head);
				break;
				
			case DELETE_EMPLOYEE:	
				deleteNode(&head);
				break;

			case SEARCH_EMPLOYEE:
				searchByEmployeeName(head);	
				break;	
			
			case PLAY_MAGIC_GAME:
                                playMagicGame(&head);
                                break;	
			
			case SORT_BY_NAME:
				sort(&head);
				break;

			case EXIT:
				puts("Exiting the program");
				another = 0;
				break;

		 	default:
				puts("Please enter correct choice");
		}
	
		displayList(head);
	}
	
	freeList(head);
   	return 0;	
}

