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

char selectPlayer(turn *t)
{
  if (t->current->piece == PAWNA || t->current->piece == QUEENA) return 'A';
  else if (t->current->piece == PAWNB || t->current->piece == QUEENB) return 'B';
  else return 'O';
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

void movePiece(board *b, turn *t, display *d)
{
  if (t->player=='A')
  {
    if (t->current==t->prev->bot->left || t->current==t->prev->bot->right)
    {
      t->current->piece = t->prev->piece;
      t->prev->piece = EMPTY;
      drawSelect(d, t->xN*64, t->yN*64);
      if (t->prev->colour == WHITE) box(d, t->x*64, t->y*64, 64, 64, 0x0);
      else box(d, t->x*64, t->y*64, 64, 64, 0xFFFFFFFF);
      deselect(t,d);
    }
    else
    {
      printf("Error: Invalid move.\n");
      runTurn(d, b, t);
    }
  }
  else
  {
    if (t->current==t->prev->top->left || t->current==t->prev->top->right)
    {
      t->current->piece = t->prev->piece;
      t->prev->piece = EMPTY;
      drawSelect(d, t->xN*64, t->yN*64);
      if (t->prev->colour == WHITE) box(d, t->x*64, t->y*64, 64, 64, 0x0);
      else box(d, t->x*64, t->y*64, 64, 64, 0xFFFFFFFF);
      deselect(t, d);
    }
    else
    {
      printf("Error: Invalid move.\n");
      runTurn(d, b, t);
    }
  }
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

void runTurn(display *d, board *b, turn *t)
{
  int *coord = mouse(d);
  t->x = coord[0];
  t->y = coord[1];
  getCoords(b, t);
  selectPiece(b, t, d);
  if (selectPlayer(t)=='O')
  {
    printf("Error: No piece selected.\n");
    t->prev = t->current;
    deselect(t, d);
    free(coord);
    runTurn(d, b, t);
  }
  else if (selectPlayer(t)!=t->player)
  {
    printf("Error: Piece from wrong player selected.\n");
    t->prev = t->current;
    deselect(t, d);
    free(coord);
    runTurn(d, b, t);
  }
  else
  {
    t->prev = t->current;
    int *coordN = mouse(d);
    t->xN = coordN[0];
    t->yN = coordN[1];
    getCoordsN(b, t);
    selectNextPiece(b, t, d);
    while ((t->player=='A')&&(t->current->piece==PAWNA || t->current->piece==QUEENA))
    {
      deselect(t, d);
      if (t->current==t->prev)
      {
        printf("Error: Same piece selected.\n");
        drawSelect(d, t->x*64, t->y*64);
      }
      t->prev = t->current;
      t->x = t->xN;
      t->y = t->yN;
      int *coordNN = mouse(d);
      t->xN = coordNN[0];
      t->yN = coordNN[1];
      getCoordsN(b, t);
      selectNextPiece(b, t, d);
      deselect(t, d);
      free(coordNN);
    }
    while ((t->player=='B')&&(t->current->piece==PAWNB || t->current->piece==QUEENB))
    {
      deselect(t, d);
      if (t->current==t->prev)
      {
        printf("Error: Same piece selected.\n");
        drawSelect(d, t->x*64, t->y*64);
      }
      t->prev = t->current;
      t->x = t->xN;
      t->y = t->yN;
      int *coordNN = mouse(d);
      t->xN = coordNN[0];
      t->yN = coordNN[1];
      getCoordsN(b, t);
      selectNextPiece(b, t, d);
      deselect(t, d);
      free(coordNN);
    }

    movePiece(b, t, d);
    t->prev = t->current;
    free(coord);
    free(coordN);

    if (t->player=='A') t->player='B';
    else t->player='A';
  }
}

void runGame(display *d, board *b)
{
  turn *t = malloc(sizeof(turn));
  t->player = 'A';
  while (b->gameover==false)
  {
    printf("\n%c\n", t->player);
    runTurn(d, b, t);
  }
  free(t);
}
