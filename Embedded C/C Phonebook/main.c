#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "Basic_Types.h"
int32_t main()
{
  int8_t n;
  printf("\n**********************************************");
  printf("\n PhoneBook INFORMATION SYSTEM");
  printf("\n**********************************************");
  printf("\n1. Add new element");
  printf("\n2. Delete Element");
  printf("\n3. Search for an element");
  printf("\n4. Edit an Element");
  printf("\n5. Exit");
  printf("\n**********************************************");
  printf("\nPlease enter your option< 1 / 2 / 3 / 4 / 5 >: ");
  scanf("%d", &n);

  switch(n){
    case (int8_t)1:
        newRecord();
        break;
    case (int8_t)2:
        deletElement();
        break;
    case (int8_t)3:
        searchForElement();
        break;
    case (int8_t)4:
        editeElement();
        break;
    case (int8_t)5:
        printf("\n*** Thanks for using the program! Goodbye. ***\n");
        exit(0);
        break;
    default:
        printf("\nError! Wrong Number is Entered\nPlease Try Again");
        break;
    }
   return 0;
}
