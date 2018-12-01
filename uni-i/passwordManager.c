#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

int maxlengthInput = 1024; //max length fgets() can use
int maxlengthUsername = maxlengthInput; //length for both muser and user
int maxlengthPassword = maxlengthInput; //length for both muser and user

//structure for a set of credidentials
typedef struct
{
  char *username;
  char *password;
} cred;

//structure for a login for one website, with 'site' being an index
typedef struct
{
  char *site;
  cred *cred;
} user;

//structure for a master login, with a pointer to their stored accounts
typedef struct
{
  cred *cred;
  array *users;
} muser;

typedef struct
{
  muser *content;
  size_t length;
  size_t size;
} array;

//initialised a new array struct
void arrayMuserInit(array *arr, size_t i)
{
  if (i>0)
  {
    arr->content = malloc(i*sizeof(muser *));
    arr->length = 0;
    arr->size = i;
  }
  else
  {
    fprintf(stderr, "Error: function arrayMuserInit(x) failed
                    with invalid x parameter!");
  }
}

//insert an element into the content of the array struct,
// and allocate more memory if needed by f=1.5
void arrayMuserInsert(array *arr, muser *element)
{
  if (arr->length==arr->size)
  {
    arr->size *= 1.5;
    arr->content = realloc(arr->content, arr->size*sizeof(muser *));
  }
  arr->content[arr->length++] = element;
}

//frees up the dymnamic array
void arrayMuserFree(array *arr)
{
  free(arr->content);
  arr->content = NULL;
  arr->length = arr->size = 0;
}



//initialised a new array struct
void arrayUserInit(array *arr, size_t i)
{
  if (i>0)
  {
    arr->content = malloc(i*sizeof(user *));
    arr->length = 0;
    arr->size = i;
  }
  else
  {
    fprintf(stderr, "Error: function arrayUserInit(x) failed
                    with invalid x parameter!");
  }
}

//insert an element into the content of the array struct,
// and allocate more memory if needed by f=1.5
void arrayUserInsert(array *arr, user *element)
{
  if (arr->length==arr->size)
  {
    arr->size *= 1.5;
    arr->content = realloc(arr->content, arr->size*sizeof(user *));
  }
  arr->content[arr->length++] = element;
}

//frees up the dymnamic array
void arrayUserFree(array *arr)
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
void newMUser(char *name, char *pass, array *musers)
{
  muser *new = malloc(sizeof(muser));
  cred *newCred = malloc(sizeof(cred));
  new->cred = newCred;
  newCred->username = mallocString(name);
  newCred->password = mallocString(pass);
  arrayMuserInsert(musers, new);
}

int countMUsers(array *arr)
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
    if (!strcmp(inputStdin, va_arg(valist, char *))) return i;
  }
  va_end(valist);
  return -1;
}

bool checkMUsers(char option, char *string, array *musers)
{
  if (option=='u')
  {
    for (int i=1;i<musers->length;i++)
    {
      if (!strcmp(musers->content[i].cred->username,string)) return true;
    }
    return false;
  }
  else if (option=='p')
  {
    for (int i=1;i<musers->length;i++)
    {
      if (!strcmp(musers->content[i].cred->password,string)) return true;
    }
    return false;
  }
  else fprintf(stderr, "Error: function checkMusers(x)
                        failed with invalid x parmeter!\n");
}

//reqests a username and password from stdin (with validation)
void reqCred(array *musers, bool hasAccount)
{
  printf("Enter a username: ");
  char name[maxlengthUsername];
  fgets(name, maxlengthInput, stdin);
  name[strlen(name) - 1] = '\0';
  if (strlen(name)>maxlengthUsername)
  {
    fprintf(stderr, "Invalid Username: Username too long.\n\n");
    reqCred(musers, hasAccount);
  }
  printf("Enter a password: ");
  char pass[maxlengthPassword];
  fgets(pass, maxlengthInput, stdin);
  pass[strlen(pass) - 1] = '\0';
  if (strlen(pass)>maxlengthPassword)
  {
    fprintf(stderr, "Invalid Password: Password too long.\n\n");
    reqCred(musers, hasAccount);
  }

  if (hasAccount==true)
  {
    //checks credidentials
    if (checkMUsers(u, name, musers))
    {
      if (checkMUsers(p, pass, musers))
      {
        //do something when u and p are valid
      }
      else
      {
        printf("Incorrect Password. Please try again.\n");
        reqCred(musers, true);
      }
    }
    else
    {
      printf("Incorrect Username.\n");
      reqLogin(musers);
    }
  }
  else newMUser(name, pass, musers);
}

//requests a username from stdin
void reqLogin(array *musers)
{
  printf("Do you have a Master account? [y/n]: ");
  int r = checkInput(4, "y","Y","n","N");
  if (r==0 || r==1){(reqCred(musers, true))}
  else if (r==2 || r==3){reqCred(musers, false)}
  else
  {
    fprintf(stderr, "Invalid Input: Please type 'y'/'n' for yes/no.\n\n");
    reqLogin(musers);
  }
}

//checks if a file exists
bool fileCheck(FILE *file)
{
  if ((file = fopen("pmdata.txt", "r"))) return true;
  else return false;
}

//opens file or creates one with RW permissions if it doesnt exist
array *setup()
{
  FILE *file = NULL;
  if (fileCheck(file)) file = fopen("pmdata.txt", "r+");
  else file = fopen("pmdata.txt", "w+");
  array *musers = malloc(sizeof(array));
  arrayMuserInit(musers, 1);
  return musers;
  fclose(file);
}

void options(array *musers)
{
  printf("------------------------------------------------------------\n");
  printf("All options can be accessed by typing './passwordManager x' \n");
  printf("where x is the option name as displayed in quotation marks. \n");
  printf("------------------------------------------------------------\n\n");
  printf("'login' : Allows a Master Username/Password to be inputted. \n");
  printf("'exit'  : Clears all credentials including master users. \n\n");
  printf("------------------------------------------------------------\n\n");
  printf("Enter an option: ");
  int r = checkInput(2, "login","exit");
  if (r==0){reqLogin(musers);}
  if (r==1){arrayMuserFree(musers);}
}

void test()
{
}

int main(int n, char *args[n])
{
  setbuf(stdout, NULL);
  setup();

  if (n == 1)
  {
    options(musers);
  }
  else if (n == 2)
  {
    if (!strcmp(args[1],"login"))
    {
      reqLogin(musers);
    }
    else if (!strcmp(args[1],"exit"))
    {
      arrayMuserFree(musers);
    }
    else fprintf(stderr, "Invalid Input: Option not found.\n");
  }
  else
  {
    fprintf(stderr, "Invalid Input: Use './passwordManager' to show options.\n");
    return -1;
  }
}
