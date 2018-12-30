#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "display.h"
#include "game.h"
#include "logic.h"

void deselect(turn *t, display *d)
{
  if (t->prev->piece == PAWNA) pawn(d, t->x*64, t->y*64, 0xFF634700);
  else if (t->prev->piece == QUEENA) queen(d, t->x*64, t->y*64, 0xFF634700);
  else if (t->prev->piece == PAWNB) pawn(d, t->x*64, t->y*64, 0x0198E100);
  else if (t->prev->piece == QUEENB) queen(d, t->x*64, t->y*64, 0x0198E100);
}

void selectPlayer(turn *t)
{
  if (t->current->piece == PAWNA) t->player = 'A';
  else if (t->current->piece == QUEENA) t->player = 'A';
  else if (t->current->piece == PAWNB) t->player = 'B';
  else if (t->current->piece == QUEENB) t->player = 'B';
  else t->player = 'O';
  printf("...%c...", t->player);
}

void selectNextPiece(board *b, turn *t, display *d)
{
  b->current = b->topleft;
  for (int i=0;i<t->xN;i++)
  {
    b->current = b->current->right;
  }
  for (int j=0;j<t->yN;j++)
  {
    b->current = b->current->bot;
  }
  t->current = b->current;
  b->current = b->topleft;
  if (t->current->piece!=EMPTY && t->prev->piece!=EMPTY)
  {
    drawSelect(d, t->xN*64, t->yN*64);
  }
  else
  {
    printf("Error: No piece selected.\n");
    deselect(t, d);
  }
}

void selectPiece(board *b, turn *t, display *d)
{
  b->current = b->topleft;
  for (int i=0;i<t->x;i++)
  {
    b->current = b->current->right;
  }
  for (int j=0;j<t->y;j++)
  {
    b->current = b->current->bot;
  }
  t->current = b->current;
  b->current = b->topleft;
  if (t->current->piece!=EMPTY) drawSelect(d, t->x*64, t->y*64);
  else
  {
    printf("Error: No piece selected.\n");
  }
}

void handlerSelection(board *b, turn *t, display *d)
{
  if (t->prev->piece==PAWNA)
  {
    if (t->current->piece==PAWNA)
    {
      deselect(t, d);
      selectNextPiece(b, t, d);
    }
    else
    {
      printf("Error: Not a valid move.\n");
      deselect(t, d);
    }
  }
  else if (t->prev->piece==PAWNB)
  {
    if (t->current->piece==PAWNB)
    {
      deselect(t, d);
      selectNextPiece(b, t, d);
    }
    else
    {
      printf("Error: Not a valid move.\n");
      deselect(t, d);
    }
  }
}

void movePiece(board *b, turn *t, display *d)
{
  if (t->prev->piece==EMPTY)
  {
    printf("Error: No piece selected.\n");
    deselect(t, d);
  }
  else if (t->prev==t->current)
  {
    printf("Error: Same piece selected.\n");
    deselect(t, d);
  }
  handlerSelection(b, t, d);
}

void getCoords(board *b, turn *t)
{
  div_t posx = div(t->x, 64);
  div_t posy = div(t->y, 64);
  t->x = posx.quot;
  t->y = posy.quot;
}

void getCoordsN(board *b, turn *t)
{
  div_t posx = div(t->xN, 64);
  div_t posy = div(t->yN, 64);
  t->xN = posx.quot;
  t->yN = posy.quot;
}

void runTurn(display *d, board *b)
{
  turn *t = malloc(sizeof(turn));
  int *coord = mouse(d);
  t->x = coord[0];
  t->y = coord[1];
  getCoords(b, t);
  selectPiece(b, t, d);
  selectPlayer(t);
  t->prev = t->current;
  int *coordN = mouse(d);
  t->xN = coordN[0];
  t->yN = coordN[1];
  getCoordsN(b, t);
  selectNextPiece(b, t, d);
  movePiece(b, t, d);
  free(t);
  free(coord);
  free(coordN);
}

void runGame(display *d, board *b)
{
  for (int i=0;i<4;i++) {runTurn(d, b);}
}
