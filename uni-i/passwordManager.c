#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

int usernameMax = 20;

typedef struct
{
  char *content;
  size_t length;
  size_t size;
} array;

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
  user *accs;
} muser;

//initialised a new array struct
void arrayInit(array *arr, size_t i)
{
  arr->content = malloc(i*sizeof(char));
  arr->length = 0;
  arr->size = i;
}

//insert an element into the content of the array struct,
// and allocate more memory if needed by f=1.5
void arrayInsert(array *arr, char element)
{
  if (arr->length==arr->size)
  {
    arr->size *= 1.5;
    arr->content = realloc(arr->content, arr->size*sizeof(char));
  }
  arr->content[arr->length++] = element;
}

//frees up the dymnamic array
void arrayFree(array *arr)
{
  free(arr->content);
  arr->content = NULL;
  arr->length = arr->size = 0;
}

void arrayTake(char src[], char sub[], int n)
{
  for (int i=0;i<n;i++)
  {
    sub[i]=src[i];
  }
}

//creates a new masteruser
//muser *newMUser()
//{

//}

int countMUsers()
{
  int count=0;
  FILE *file = fopen("pmdata.txt", "r+");
  fclose(file);
  return count;
}

//checks username against file store
bool checkUsername(char *line)
{
  FILE *file = fopen("pmdata.txt", "r+");
  fprintf(file, "%s", line);
  fprintf(file, ";");
  fclose(file);
  return true;
  //fgetc(line, usernameMax+1, file); //read every char until a ;
}

//requests an input and checks it against a given string
bool checkInput(int num,...)
{
  va_list valist;
  va_start(valist, num);
  char inputStdin[100];
  fgets(inputStdin, 100, stdin);
  inputStdin[strlen(inputStdin) - 1] = '\0';
  for (int i=0;i<num;i++)
  {
    if (strlen(inputStdin)==0) return false;
    if (!strcmp(inputStdin, va_arg(valist, char *))) return true;
  }
  va_end(valist);
  return false;
}

//requests a username from stdin
void reqLogin()
{
  printf("Do you have a Master account? [y/n]: ");
  if (checkInput(4, "y","n","Y","N")){}
  else fprintf(stderr, "Invalid Input: Please type 'y'/'n' for yes/no.\n");
}

//checks if a file exists
bool fileCheck(FILE *file)
{
  if ((file = fopen("pmdata.txt", "r"))) return true;
  else return false;
}

//opens file or creates one with RW permissions if it doesnt exist
void setup()
{
  FILE *file = NULL;
  if (fileCheck(file)) file = fopen("pmdata.txt", "r+");
  else file = fopen("pmdata.txt", "w+");
  //creates a dynamic array to point to all masterusers
  muser *mlogins = malloc(sizeof(muser)*countMUsers());
  fclose(file);
}

void options()
{
  printf("------------------------------------------------------------\n");
  printf("All options can be accessed by typing './passwordManager x' \n");
  printf("where x is the option name as displayed in quotation marks. \n");
  printf("------------------------------------------------------------\n\n");
  printf("'login' : Allows a Master Username/Password to be inputted. \n\n");
  printf("------------------------------------------------------------\n");
}

int main(int n, char *args[n])
{
  setbuf(stdout, NULL);
  if (n == 1)
  {
    setup();
    reqLogin();
  }
  else if (n == 4)
  {
  }
  else
  {
    fprintf(stderr, "Use ./passwordManager to view options or perform first-time setup.\n");
    return -1;
  }
}
