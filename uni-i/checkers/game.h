#include <stdbool.h>

typedef enum COLOUR {WHITE = 0, BLACK = 1} COLOUR;
typedef enum PIECE {EMPTY = 0, PAWNA, PAWNB, QUEENA, QUEENB} PIECE;

struct square
{
  COLOUR colour;
  PIECE piece;
  struct square *top;
  struct square *left;
  struct square *bot;
  struct square *right;
};

struct board
{
  struct square *topleft;
  struct square *current;
  bool gameover;
  int size;
};

typedef struct board board;
typedef struct square square;

//makes a new row out of squares and links correctly
void newRow(board *b, square *start);
//links rows made by newRow - by the end of this the board is complete
void linkRows(board *b, square *start);
//makes a starting square (top-left) and makes a new linked board
void newBoardSquares(board *b);
//returns a pointer to a newly malloc'ed board struct
board *newBoard();
