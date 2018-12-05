#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "hash.h"

//initialised a new array struct
void arrayInit(array *arr, size_t i)
{
  if (i>0)
  {
    arr->content = malloc(i*sizeof(char **));
    arr->length = 0;
    arr->size = i;
  }
  else
  {
    fprintf(stderr, "Error: function arrayInit(x) failed with invalid x parameter!\n");
  }
}

void arrayFree(array *arr)
{
  for (int i=32;i>0;i--)
  {
    free(&arr[i].length);
    free(&arr[i].size);
    free(&arr[i].content);
    free(&arr[i]);
  }
  free(arr);
}

//insert an element into the content of the array struct,
// and allocate more memory if needed by f=1.5
void arrayInsert(array *arr, char **element)
{
  if (arr->length==arr->size)
  {
    arr->size *= 2;
    arr->content = realloc(arr->content, arr->size*sizeof(element));
  }
  arr->content[arr->length] = element;
  arr->length++;
}

char *mallocString(const char input[])
{
  char *s = malloc((sizeof(char)*strlen(input))+1);
  return s;
}

int hash(char *s)
{
  int hash = 7;
  for (int i = 0; i < strlen(s); i++) {
    hash = hash*31 + s[i];
  }
  return hash;
}

int lookup(array *ht)
{
  printf("Enter an name: ");
  char name[100];
  fgets(name, 100, stdin);
  name[strlen(name) - 1] = '\0';
  printf("\n");
  int h = hash(name);
  int i = hash(name)%32;

  for (int j=0;j<ht[i].length;j++)
  {
    if (!strcmp(*ht[i].content[j], name))
    {
      printf("Name: %s \nPosition: %d-%d\nHash ID: %d\n\n", *ht[i].content[j], i, j, h);
      return i;
    }
  }
  fprintf(stderr, "Not in hash table.\n\n");

  return -1;
}

bool insert(array *ht)
{
  printf("Enter an name: ");
  char name[100];
  fgets(name, 100, stdin);
  name[strlen(name) - 1] = '\0';
  printf("\n");
  int i = hash(name)%32;
  //if (ht[i].length==0)
  //{
  for (int j=0;j<ht[i].length;j++)
  {
    if (!strcmp(*ht[i].content[j], name))
    {
      fprintf(stderr, "Entry already in hash table.\n");
      return false;
    }
  }
  char **n = malloc(sizeof(n));
  *n = mallocString(name);
  strcpy(*n, name);
  arrayInsert(&ht[i], n);
  return true;
}

int checkInput(int num,...)
{
  va_list valist;
  va_start(valist, num);
  char inputStdin[1024];
  fgets(inputStdin, 1024, stdin);
  inputStdin[strlen(inputStdin) - 1] = '\0';
  for (int i=0;i<num;i++)
  {
    if (strlen(inputStdin)==0) return -1;
    if (!strcmp(inputStdin, va_arg(valist, char *))) {return i;}
  }
  va_end(valist);
  return -1;
}

void reqOptions(array *ht)
{
  printf("Enter an option: ");
  int r = checkInput(3, "insert","lookup","exit");
  printf("\n");
  if (r==0){insert(ht);reqOptions(ht);}
  else if (r==1){lookup(ht);reqOptions(ht);}
  else if (r==2){arrayFree(ht);exit(0);}
  else
  {
    fprintf(stderr, "Invalid Input: Option not found.\n\n");
    reqOptions(ht);
  }
}

void options(array *ht)
{
  printf("------------------------------------------------------------\n");
  printf("All options can be accessed by typing './hash x' \n");
  printf("where x is the option name as displayed in quotation marks. \n");
  printf("------------------------------------------------------------\n");
  printf("'insert' : Inserts a string into the hash table.\n");
  printf("'lookup' : Looks up a string in the hash table. \n");
  printf("'exit'   : Frees up memory and exits the program. \n");
  printf("------------------------------------------------------------\n\n");
  reqOptions(ht);
}

int main(int n, char *args[n])
{
  array *ht = malloc(sizeof(ht));
  for (int i=0;i<32;i++)
  {
    arrayInit(&ht[i],1);
  }

  if (n == 1)
  {
    options(ht);
  }
  else if (n == 2)
  {
    if (!strcmp(args[1],"insert"))
    {
      insert(ht);
    }
    else if (!strcmp(args[1],"lookup"))
    {
      lookup(ht);
    }
    else if (!strcmp(args[1],"exit"))
    {
      arrayFree(ht);
      exit(0);
    }
    else fprintf(stderr, "Invalid Option.\n");
  }
  else fprintf(stderr, "Use ./hash to view options or ./hash x where x is 'insert' or 'lookup'.\n");
}
