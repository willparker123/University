#include "game.h"
#include "display.h"
#include "logic.h"
#include "play.h"
#include <stdlib.h>

void drawPieces(board *b, display *d)
{
  int coord[2] = {0, 0};
  b->current = b->topleft;
  square *currentCol = b->topleft;
  for (int j=0;j<b->size;j++)
  {
    for (int i=0;i<b->size;i++)
    {
      if (b->current->piece == PAWNA) pawn(d, coord[0], coord[1], 0xFF634700);
      else if (b->current->piece == PAWNB) pawn(d, coord[0], coord[1], 0x0198E100);
      else if (b->current->piece == QUEENA) queen(d, coord[0], coord[1], 0xFF634700);
      else if (b->current->piece == QUEENB) queen(d, coord[0], coord[1], 0x0198E100);
      coord[0] = coord[0]+64;
      if (b->current->right!=NULL) b->current = b->current->right;
    }
    coord[0] = 0;
    coord[1] = coord[1]+64;
    currentCol = currentCol->bot;
    b->current = currentCol;
  }
  b->current = b->topleft;
}

void drawSquares(board *b, display *d)
{
  int coord[2] = {0, 0};
  b->current = b->topleft;
  square *currentCol = b->topleft;
  for (int j=0;j<b->size;j++)
  {
    for (int i=0;i<b->size;i++)
    {
      if (b->current->colour == WHITE) box(d, coord[0], coord[1], 64, 64, 0x0);
      else box(d, coord[0], coord[1], 64, 64, 0xFFFFFFFF);
      coord[0] = coord[0]+64;
      if (b->current->right!=NULL) b->current = b->current->right;
    }
    coord[0] = 0;
    coord[1] = coord[1]+64;
    currentCol = currentCol->bot;
    b->current = currentCol;
  }
  b->current = b->topleft;
}

display *drawBoard(board *b)
{
  display *d = newDisplay("Checkers", b->size*64, b->size*64);
  drawSquares(b, d);
  drawPieces(b, d);
  return d;
}

int main()
{
  board *b = newBoard();
  b->current = b->topleft;
  display *d = drawBoard(b);
  runGame(d, b);
}
