#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct cell cell;
typedef struct matrix matrix;
typedef int item;

struct cell
{
  int *id;
  item x;
};

struct matrix
{
  cell *x;
  cell *y;
  cell *z;
  int *size;
};

matrix *makeMatrix(int *size)
{
  matrix *m = malloc(sizeof(matrix));
  //for (int i=0;;i++)
}

void freeMatrix(matrix *m)
{
}

int *sizeToInt(char x[], char y[], char z[])
{
  int size[3];
  size[0] = atoi(x);
  size[1] = atoi(y);
  size[2] = atoi(z);
  printf("%d %d %d\n", size[0], size[1], size[2]);
  return size;
}

bool checkSize(char x[], char y[], char z[])
{
  int i=0;
  while (x[i]!='\0')
  {
    if (isdigit(x[i])==0) return false;
    else i++;
  }
  int j=0;
  while (y[j]!='\0')
  {
    if (isdigit(y[j])==0) return false;
    else j++;
  }
  int k=0;
  while (z[k]!='\0')
  {
    if (isdigit(z[k])==0) return false;
    else k++;
  }
  return true;
}

int main(int n, char *args[n])
{
    setbuf(stdout, NULL);
    if (n == 1){} //test();
    else if (n == 4)
    {
      if (checkSize(args[1], args[2], args[3]))
      {
        sizeToInt(args[1], args[2], args[3]);
      }
      else
      {
        fprintf(stderr, "Error: x,y,z must be integers\n");
        return -1;
      }
    }
    else {
        fprintf(stderr, "Use:   ./matrix   or   ./matrix x y z\n");
        fprintf(stderr, "where x,y,z is the size of the matrix in those directions\n");
        return -1;
    }
}
