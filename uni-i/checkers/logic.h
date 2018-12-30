struct turn
{
  int x;
  int y;
  int xN;
  int yN;
  char player;
  square *current;
  square *prev;
};

typedef struct turn turn;

//runs the game (takes turns and computes logic)
void runGame(display *d, board *b);

//runs a single turn
void runTurn(display *d, board *b, turn *t);

//gets the coords of the piece selected
void getCoords(board *b, turn *t);

//sets turn->current to the selected piece
void selectPiece(board *b, turn *t, display *d);

//returns A,B or O based on the piece selected.
char selectPlayer(turn *t);

//removes the yellow selection from the first click
void deselect(turn *t, display *d);

//similar to selectPiece but selectPiece's result is now t->prev.
void selectNextPiece(board *b, turn *t, display *d);

//similar to getCoords but uses xN and yN (next position -pos to be moved to).
void getCoordsN(board *b, turn *t);

//checks for valid moves and moves the selected piece
void movePiece(board *b, turn *t, display *d);
