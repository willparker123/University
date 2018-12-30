#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "display.h"

void newRow(board *b, square *start)
{
  square *c = start;
  for (int i=0;i<b->size;i++)
  {
    square *newSquare = malloc(sizeof(square));
    newSquare->colour = 1-(c->colour);
    c->right = newSquare;
    newSquare->left = c;
    if (c->top == NULL) newSquare->top = NULL;
    else
    {
      newSquare->top = c->top->right;
      c->top->right->bot = newSquare;
    }
    c = c->right;
  }
  c->right = NULL;
}

void linkRows(board *b, square *start)
{
  square *c = start;
  for (int i=0;i<b->size;i++)
  {
    square *cbot = malloc(sizeof(square));
    cbot->colour = 1-(c->colour);
    cbot->left = NULL;
    c->bot = cbot;
    cbot->top = c;
    newRow(b, c);
    c = cbot;
  }

  c = c->top;
  free(c->bot);
  while (c->right!=NULL)
  {
    c->bot = NULL;
    c = c->right;
  }
  c->bot = NULL;
}

void newBoardSquares(board *b)
{
  square *start = malloc(sizeof(square));
  b->topleft = start;
  b->current = start;
  start->colour = BLACK;
  start->top = NULL;
  start->left = NULL;
  linkRows(b, start);
}

void newBoardPlayers(board *b)
{
  b->current = b->topleft;
  square *currentCol = b->topleft;
  bool p = true;
  for (int j=0;j<3;j++)
  {
    for (int i=0;i<b->size;i++)
    {
      if (p) b->current->piece = PAWNA;
      else b->current->piece = EMPTY;
      p = !p;
      if (b->current->right!=NULL) b->current = b->current->right;
    }
    p = !p;
    currentCol = currentCol->bot;
    b->current = currentCol;
  }
  //adds spare lines
  for (int w=0;w<b->size-6;w++)
  {
    for (int i=0;i<b->size;i++)
    {
      b->current->piece = EMPTY;
      if (b->current->right!=NULL) b->current = b->current->right;
    }
    currentCol = currentCol->bot;
    b->current = currentCol;
  }

  for (int j=0;j<3;j++)
  {
    for (int i=0;i<b->size;i++)
    {
      if (p) b->current->piece = PAWNB;
      else b->current->piece = EMPTY;
      p = !p;
      if (b->current->right!=NULL) b->current = b->current->right;
    }
    p = !p;
    currentCol = currentCol->bot;
    b->current = currentCol;
  }
  b->current = b->topleft;
}

board *newBoard()
{
  board *b = malloc(sizeof(board));
  b->size = 8;
  newBoardSquares(b);
  newBoardPlayers(b);
  return b;
}
