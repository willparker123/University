#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "passwordManager.h"

int maxlengthInput = 1024; //max length fgets() can use
int maxlengthUsername = 100; //length for both muser and user
int maxlengthPassword = 100; //length for both muser and user

//initialised a new array struct
void arrayMUserInit(arrayMUsers *arr, size_t i)
{
  if (i>0)
  {
    arr->content = malloc(i*sizeof(muser *));
    arr->length = 0;
    arr->size = i;
  }
  else
  {
    fprintf(stderr, "Error: function arrayMuserInit(x) failed with invalid x parameter!\n");
  }
}

//insert an element into the content of the array struct,
// and allocate more memory if needed by f=1.5
void arrayMUserInsert(arrayMUsers *arr, muser *element)
{
  if (arr->length==arr->size)
  {
    arr->size *= 1.5;
    arr->content = realloc(arr->content, arr->size*sizeof(muser *));
  }
  arr->content[arr->length++] = *element;
}

//frees up the dymnamic array
void arrayMUserFree(arrayMUsers *arr)
{
  free(arr->content);
  arr->content = NULL;
  arr->length = arr->size = 0;
}



//initialised a new array struct
void arrayUserInit(arrayUsers *arr, size_t i)
{
  if (i>0)
  {
    arr->content = malloc(i*sizeof(user *));
    arr->length = 0;
    arr->size = i;
  }
  else
  {
    fprintf(stderr, "Error: function arrayUserInit(x) failed with invalid x parameter!\n");
  }
}

//insert an element into the content of the array struct,
// and allocate more memory if needed by f=1.5
void arrayUserInsert(arrayUsers *arr, user *element)
{
  if (arr->length==arr->size)
  {
    arr->size *= 1.5;
    arr->content = realloc(arr->content, arr->size*sizeof(user *));
  }
  arr->content[arr->length++] = *element;
}

//frees up the dymnamic array
void arrayUserFree(arrayUsers *arr)
{
  free(arr->content);
  arr->content = NULL;
  arr->length = arr->size = 0;
}



//takes n chars from the array and puts them in the arary sub
void arrayTake(char src[], char sub[], int n)
{
  for (int i=0;i<n;i++)
  {
    sub[i]=src[i];
  }
}

char *mallocString(const char input[])
{
  char *s = malloc((sizeof(char)*strlen(input))+1);
  return s;
}

//creates a new masteruser
void newMUser(char *name, char *pass, arrayMUsers *musers)
{
  muser *new = malloc(sizeof(muser));
  cred *newCred = malloc(sizeof(cred));
  new->cred = newCred;
  newCred->username = mallocString(name);
  newCred->password = mallocString(pass);
  arrayMUserInsert(musers, new);
}

int countMUsers(arrayMUsers *arr)
{
  return (arr->length);
}

//checks username against file store
bool writeToFile(char *line)
{
  FILE *file = fopen("pmdata.txt", "r+");
  fprintf(file, "%s", line);
  fprintf(file, ";");
  fclose(file);
  return true;
  //fgetc(line, usernameMax+1, file); //read every char until a ;
}

//requests an input and checks it against a given string
int checkInput(int num,...)
{
  va_list valist;
  va_start(valist, num);
  char inputStdin[maxlengthInput];
  fgets(inputStdin, maxlengthInput, stdin);
  inputStdin[strlen(inputStdin) - 1] = '\0';
  for (int i=0;i<num;i++)
  {
    if (strlen(inputStdin)==0) return -1;
    if (!strcmp(inputStdin, va_arg(valist, char *))) {printf("\n**%s**\n",inputStdin); return i;}
  }
  printf("\n**%s**\n",inputStdin);
  va_end(valist);
  return -1;
}

bool checkMUsers(char option, char *string, arrayMUsers *musers)
{
  if (option=='u')
  {
    for (int i=1;i<musers->length-1;i++)
    {
      muser *pMU = &musers->content[i];
      cred *pMUC = pMU->cred;
      char *pName = pMUC->username;
      if (!strcmp(pName,string)) {return true;break;}
    }
    return false;
  }
  else if (option=='p')
  {
    for (int i=1;i<musers->length-1;i++)
    {
      muser *pMU = &musers->content[i];
      cred *pMUC = pMU->cred;
      char *pPass = pMUC->password;
      if (!strcmp(pPass,string)) {return true;break;}
    }
    return false;
  }
  else fprintf(stderr, "Error: function checkMusers(x) failed with invalid x parmeter!\n");
  return false;
}

//reqests a username and password from stdin (with validation)
void reqCredMUser(arrayMUsers *musers, bool hasAccount)
{
  if (hasAccount==true)
  {
    printf("Enter a username: ");
    char name[maxlengthUsername];
    fgets(name, maxlengthInput, stdin);
    name[strlen(name) - 1] = '\0';
    if (strlen(name)>maxlengthUsername)
    {
      fprintf(stderr, "Invalid Username: Username too long.\n\n");
      reqCredMUser(musers, hasAccount);
    }
    printf("\n**%s**\n",name);
    bool correctUsername = checkMUsers('u', name, musers);
    printf("%d",correctUsername);
    //checks credidentials
    if (correctUsername)
    {
      printf("Enter a password: ");
      char pass[maxlengthPassword];
      fgets(pass, maxlengthInput, stdin);
      pass[strlen(pass) - 1] = '\0';
      if (strlen(pass)>maxlengthPassword)
      {
        fprintf(stderr, "Invalid Password: Password too long.\n\n");
        reqCredMUser(musers, hasAccount);
      }
      printf("\n**%s**\n",pass);
      bool correctPassword = checkMUsers('p', pass, musers);
      printf("%d",correctPassword);

      if (correctPassword)
      {
        //do something when u and p are valid
      }
      else
      {
        printf("Incorrect Password. Please try again.\n\n");
        reqCredMUser(musers, true);
      }
    }
    else
    {
      printf("Incorrect Username.\n\n");
      reqLoginMUser(musers);
    }
  }
  else
  {
    printf("Enter a username: ");
    char name[maxlengthUsername];
    fgets(name, maxlengthInput, stdin);
    name[strlen(name) - 1] = '\0';
    if (strlen(name)>maxlengthUsername)
    {
      fprintf(stderr, "Invalid Username: Username too long.\n\n");
      reqCredMUser(musers, hasAccount);
    }
    printf("Enter a password: ");
    char pass[maxlengthPassword];
    fgets(pass, maxlengthInput, stdin);
    pass[strlen(pass) - 1] = '\0';
    if (strlen(pass)>maxlengthPassword)
    {
      fprintf(stderr, "Invalid Password: Password too long.\n\n");
      reqCredMUser(musers, hasAccount);
    }
    newMUser(name, pass, musers);
    printf("Master Account created.\n\n\n");
    reqOptions(musers);
  }
}

//requests a username from stdin
void reqLoginMUser(arrayMUsers *musers)
{
  printf("Do you have a Master account? [y/n]: ");
  int r = checkInput(4, "y","Y","n","N");
  if (r==0 || r==1){reqCredMUser(musers, true);}
  else if (r==2 || r==3){reqCredMUser(musers, false);}
  else
  {
    fprintf(stderr, "Invalid Input: Please type 'y'/'n' for yes/no.\n\n");
    reqLoginMUser(musers);
  }
}

//checks if a file exists
bool fileCheck(FILE *file)
{
  if ((file = fopen("pmdata.txt", "r"))) return true;
  else return false;
}

//opens file or creates one with RW permissions if it doesnt exist
arrayMUsers *setup()
{
  FILE *file = NULL;
  if (fileCheck(file)) file = fopen("pmdata.txt", "r+");
  else file = fopen("pmdata.txt", "w+");
  fclose(file);
}

void reqOptions(arrayMUsers *musers)
{
  printf("Enter an option: ");
  int r = checkInput(2, "login","exit");
  printf("\n");
  if (r==0){reqLoginMUser(musers);}
  if (r==1){arrayMUserFree(musers);exit(0);}
  else
  {
    //fprintf(stderr, "Invalid Input: Option not found.\n\n");
    //reqOptions(musers);
  }
}

void options(arrayMUsers *musers)
{
  printf("------------------------------------------------------------\n");
  printf("All options can be accessed by typing './passwordManager x' \n");
  printf("where x is the option name as displayed in quotation marks. \n");
  printf("------------------------------------------------------------\n\n");
  printf("'login' : Allows a Master Username/Password to be inputted. \n");
  printf("'exit'  : Clears all credentials including master users. \n\n");
  printf("------------------------------------------------------------\n\n");
  reqOptions(musers);
}

void test()
{
}

int main(int n, char *args[n])
{
  setbuf(stdout, NULL);
  arrayMUsers *musers = malloc(sizeof(arrayMUsers));
  arrayMUserInit(musers, 1);
  setup();

  if (n == 1)
  {
    options(musers);
  }
  else if (n == 2)
  {
    if (!strcmp(args[1],"login"))
    {
      reqLoginMUser(musers);
    }
    else if (!strcmp(args[1],"exit"))
    {
      arrayMUserFree(musers);
      exit(0);
    }
    else fprintf(stderr, "Invalid Input: Option not found.\n");
  }
  else
  {
    fprintf(stderr, "Invalid Input: Use './passwordManager' to show options or './passwordManager x' where x is an option.\n");
    return -1;
  }
}
