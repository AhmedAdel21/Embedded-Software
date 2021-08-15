#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Basic_Types.h"


struct user
{
    int8_t name[25], email[30], phoneNumber[20];
};
int8_t* TextFile = "data.txt";
#include "functions.h"

void editeElement(void){
  int32_t pointerPosition = 0,row = 0,editingRow = 0;
  FILE *file;
  struct user olduser={' ',' ',' '};
  int8_t c = 'a' ;
  int8_t line[100]="line";
  int8_t wordSearch[30] = "free";
  printf("\n**********************************************");
  printf("\n what record you want to edite ?");
  printf("\n**********************************************\n");
  printf("Enter Name, Email Or Phone: ");
  fflush(stdin);
  gets(wordSearch);
  editingRow = (int32_t)search(wordSearch);
  printRow(editingRow);
  file = fopen(TextFile, "r");
  ifFileOpened(file);
  c = (int8_t) getc(file);
  while (c != (int8_t)EOF) {
    pointerPosition++;
    if (c == '\n')
      {
        row++;
        if (row == editingRow){
          break;
        }
      }else{};
    c = (int8_t) getc(file);
    }

  fgets(line,(int16_t)sizeof(line),file);
  sscanf(line,"%s %s %s",olduser.name,olduser.email,olduser.phoneNumber);
  fclose(file);
  modifyElement(olduser,(int32_t)(pointerPosition+editingRow));


}
void modifyElement(struct user olduser,int32_t pointerPosition){
  int8_t n=0;
  FILE *file;
  printf("\n**********************************************");
  printf("\n What you want to edit ?");
  printf("\n**********************************************");
  printf("\n1. Name");
  printf("\n2. Email");
  printf("\n3. Phone");
  printf("\n4. Exit");
  printf("\n**********************************************");
  printf("\nPlease enter your option< 1 / 2 / 3 / 4 >: ");
  scanf("%d", &n);
  switch(n){
    case (int8_t)1:
        printf("Enter the new name: ");
        fflush(stdin);
        gets(olduser.name);
        break;
    case (int8_t)2:
        printf("Enter the new email: ");
        fflush(stdin);
        gets(olduser.email);
        break;
    case (int8_t)3:
        printf("Enter the new phone: ");
        fflush(stdin);
        gets(olduser.phoneNumber);
        break;
    default:
        printf("\nError! Wrong Number is Entered\nPlease Try Again");
        break;
    }

  file = fopen(TextFile,"r+");
  ifFileOpened(file);
  fseek( file, (int32_t)(pointerPosition), SEEK_SET );
  printf("%s \t %s \t %s",olduser.name,olduser.email,olduser.phoneNumber);
  fprintf(file,"%25s\t\t%30s\t\t%20s",olduser.name,olduser.email,olduser.phoneNumber);
  fclose(file); 
  printf("*********************\n");
  printf("Element is modified successfully \n");
  printf("*********************\n");
  main();
}


void printRow(int32_t rowTarget){
    FILE *fRead;
    int8_t c='a';
    int8_t line[100] = {' '};
    uint8_t row =0;
    struct user printuser;
    fRead = fopen(TextFile, "r");
    ifFileOpened(fRead);
    c = (int8_t)getc(fRead);
    while (c != (int8_t)EOF) {
      if (c == (int8_t)'\n')
      {
        row++;
        if ((int8_t)row == (int8_t)rowTarget){
          printf("%s \t\t %s \t\t %s\n",
              "Name","Email","Phone");
          fgets(line,(int16_t)sizeof(line),fRead);
          sscanf(line,"%s %s %s",printuser.name,printuser.email,printuser.phoneNumber);
          printf("%s\t\t%s\t\t%s\n",printuser.name,printuser.email,printuser.phoneNumber);
          break;
        }
      }
      c = (int8_t)getc(fRead);
    }
    fclose(fRead);

}
void searchForElement(void){
  int8_t wordSearch[30] ={' '};
  int32_t elementRow;
  printf("Enter Name, Email Or Phone: ");
  fflush(stdin);
  gets(wordSearch);
  elementRow = (int32_t)search(wordSearch);
  printRow(elementRow);
  main();
}

int32_t search(const int8_t *wordSearch){
  FILE *fRead;
  int8_t wordText[30] = {' '};
  uint32_t  element = 0;
  int32_t result = 0;
  uint8_t notfound = 0;
  fRead = fopen(TextFile,"r");
  ifFileOpened(fRead);
  printf("we are searching about -> %s \n",wordSearch);
  while (fscanf(fRead, "%s", wordText) == 1 ){
    element++;
    if(strcmp(wordSearch,wordText ) == (int32_t)0){
      notfound = (uint8_t)1;
      printf("we found it\n");
      printf("**********************************************\n");
      result = (int32_t)(element/(uint32_t)3);
      break;
    }
    memset(wordText,0,sizeof(wordText));
  }
  if (notfound == (uint8_t)0)
  {
    printf("%s Not found \n",wordSearch);
    printf("**********************************************\n");
    main();
  }

  fclose(fRead);
  return result;
}
void deleteRecord(uint32_t deletedRow){

  FILE *fRead,*fWrite;
  int8_t c;
  int32_t actualRow=0;
  fRead = fopen(TextFile, "r");
  fWrite = fopen("copy.txt", "w");
  ifFileOpened(fWrite);
  c = (int8_t)getc(fRead);
  while (c != (int8_t)EOF) {
    if (c == (int8_t)'\n')
    {
      actualRow++;
    }
    if ((int32_t)actualRow != (int32_t)deletedRow){
        putc((int32_t)c, fWrite);
    }else{};
    c = (int8_t)getc(fRead);
  }
  fclose(fRead);
  fclose(fWrite);
  remove(TextFile);
  rename("copy.txt", TextFile);
  printf("The deletion process was successful \n");
  main();
}
void deletElement(void){
  int8_t deletedElement[30] = {' '};
  uint32_t deletedRow=0;
  printf("\nDelete Recored with Name, Email Or Phone: ");
  fflush(stdin);
  gets(deletedElement);
  deletedRow = (uint32_t)search(deletedElement);
  deleteRecord((uint32_t)deletedRow);

}
void addRecord(struct user newuser){
  FILE *fptr;
  fptr = fopen(TextFile,"a");
  ifFileOpened(fptr);
  fprintf(fptr,"\n%25s\t\t%30s\t\t%20s",newuser.name,newuser.email,newuser.phoneNumber);
  fclose(fptr);
  printf("*********************\n");
  printf("New Record added successfully\n");
  main();
  }
void newRecord(void){
  struct user newuser = {' ', ' ', ' '};
  fflush(stdin);
  printf("\t XX The name shouldn't contain any whitespaces XX\n");
  printf("Name \t:");
  gets(newuser.name);
  fflush(stdin);
  printf("Email \t:");
  gets(newuser.email);
  fflush(stdin);
  printf("Phone \t:");
  gets(newuser.phoneNumber);
  fflush(stdin);
  addRecord(newuser);

}


void ifFileOpened( const FILE *file){
  if(file==NULL)
    {
    printf("\n xxxx file opening error xxxx:");

    exit(1);
    }else{};
}
