#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "display.h"

enum OP {DX = 0x0, DY = 0x1, PEN = 0x3, U = 0xF};

typedef struct
{
  int dx;
  int cx;
  int cy;
  bool pen;
} state;

//checks if a file exists
bool fileCheck(char *filename)
{
  filename = strcat(filename, ".sketch");
  if (fopen(filename, "r")!=NULL) return true;
  else return false;
}

FILE *openFile(char *filename)
{
  if (fileCheck(filename)) {FILE *file = fopen(filename, "r");  return file;}
  else {fprintf(stderr, "Error: file does not exist.\n");  return NULL;}
}

void closeFile(FILE *file)
{
  fclose(file);
}

//gives a file maxlengthInput
int fileLength(FILE *file)
{
  fseek(file, 0L, SEEK_END);
  int l = ftell(file);
  fseek(file, 0L, SEEK_SET);
  return l;
}

//reads file byte by byte,
unsigned char *readFile(FILE *file, unsigned char *filebytes, int bytesToRead)
{
  fseek(file, 0, SEEK_SET);
  size_t bytesRead = 0;
  bytesRead = fread(filebytes, sizeof(unsigned char), bytesToRead, file);
  return filebytes;
}

char *getFilename()
{
  printf("Enter a file name: ");
  char filename[100];
  fgets(filename, 100, stdin);
  filename[strlen(filename) - 1] = '\0';
  return filename;
}

int formatByte(unsigned char byte)
{
  int c=0;
  if ((byte>>5 & 0x1) !=0)
  {
    byte = ((~byte)+0x1) & 0x3F;
    c=-byte;
  }
  else c=byte;
  return c;
}

void opPEN(state *s, unsigned char byte)
{
  s->pen = !s->pen;
}

void opDY(state *s, unsigned char byte, display *screen)
{
  int c=formatByte(byte);

  if (s->pen==true)
  {
    line(screen, s->cx, s->cy, s->cx+s->dx, s->cy+c);
  }
  s->cx = s->cx+s->dx;
  s->cy = s->cy+c;
  s->dx = 0;
}

void opDX(state *s, unsigned char byte)
{
  int c=formatByte(byte);
  s->dx = c;
  printf("\n%d\n\n\n", c);
}

void instruction(unsigned char byte, state *s, display *screen)
{
  printf("Opcode: %02hhX\n", (byte>>6) & 0x0F);
  printf("Operand: %02hhX\n\n", byte & 0x3F);

  if (((byte>>6) & 0x0F) == DX) {opDX(s, byte & 0x3F);}
  else if (((byte>>6) & 0x0F) == DY) {opDY(s, byte & 0x3F, screen);}
  else if (((byte>>6) & 0x0F) == PEN) {opPEN(s, byte & 0x3F);}
  else fprintf(stderr, "Invalid Opcode.\n");
}

//executes instructions 1 at a time
void execute(int bytesToRead, unsigned char *filebytes, state *s, display *screen)
{
  for (int i=0;i<bytesToRead;i++)
  {
    instruction(filebytes[i], s, screen);
  }
}

void setup(state *s)
{
  s->cx = 0;
  s->cy = 0;
  s->pen = false;
  s->dx = 0;
}

void showDisplay(display *screen)
{
  end(screen);
}

int main()
{
  char *filename = getFilename();
  FILE *file = openFile(filename);
  state *s = malloc(sizeof(state));
  setup(s);

  if (file!=NULL)
  {
    int bytesToRead = fileLength(file);
    unsigned char *filebytes = malloc(sizeof(unsigned char)*bytesToRead);
    filebytes = readFile(file, filebytes, bytesToRead);
    display *screen = newDisplay("screen", 200, 200);
    printf("%d\n", bytesToRead);
    execute(bytesToRead, filebytes, s, screen);
    //instruction(0x20,s);
    //opDX(s, 0x1F & 0x3F);
    showDisplay(screen);
    closeFile(file);
    free(filebytes);
    free(screen);
  }

  free(s);
}
