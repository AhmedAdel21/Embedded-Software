#ifndef FUNCTIONS
#define FUNCTIONS
#include "Basic_Types.h"
void newRecord(void);
/*
	Function Name        : newRecord
	Function Returns     : void
	Function Arguments   : void
	Function Description : to add a new recored you just need to use this function
*/
void deletElement(void);
/*
	Function Name        : deletElement
	Function Returns     : void
	Function Arguments   : void
	Function Description : delet an element from database
*/
void editeElement(void);
/*
	Function Name        : editeElement
	Function Returns     : void
	Function Arguments   : void
	Function Description : to edit an element
*/
void searchForElement(void);
/*
	Function Name        : searchForElement
	Function Returns     : void
	Function Arguments   : void
	Function Description : for searching for an element
*/

void ifFileOpened(const FILE *file);
/*
	Function Name        : ifFileOpened
	Function Returns     : void
	Function Arguments   : FILE *file
	Function Description : make sure that the file is opened
*/
int32_t search(const int8_t *wordSearch);
/*
	Function Name        : search
	Function Returns     : return a row number of the element that we search for
	Function Arguments   : char *wordSearch
	Function Description : search for an element in database and return its row number
*/
void deleteRecord(uint32_t deletedRow);
/*
	Function Name        : deleteRecord
	Function Returns     : void
	Function Arguments   : uint32_t deletedRow
	Function Description : delet a specific record
*/
void addRecord(struct user newuser);
/*
	Function Name        : addRecord
	Function Returns     : void
	Function Arguments   : struct user newuser
	Function Description : add a record to database
*/
void modifyElement(struct user olduser,int32_t pointerPosition);
/*
	Function Name        : modifyElement
	Function Returns     : void
	Function Arguments   : struct user olduser,int32_t pointerPosition
	Function Description : get an element to edit it
*/
void printRow(int32_t rowTarget);
/*
	Function Name        : printRow
	Function Returns     : void
	Function Arguments   : uint32_t rowTarget
	Function Description : print a specific row
*/
int32_t main(void);
/*
	the main func
*/
#endif
