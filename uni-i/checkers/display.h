// You do not need to change this file.
// The display module provides graphics for the sketch program.

// A display structure needs to be created by calling newDisplay, and then
// needs to be passed to each sketching function.
struct display;
typedef struct display display;

// Create a display object representing a plain white window of a given size.
display *newDisplay(char *title, int width, int height);

// Draw a line from (x0,y0) to (x1,y1) which is black by default.
void line(display *d, int x0, int y0, int x1, int y1);

// Draw a filled in box at (x,y) at given size.
void box(display *d, int x, int y, int width, int height, int rgba);

//Draws a 64x64 pawn with a given colour.
void pawn(display *d, int x, int y, int rgba);

//Draws a 64x64 queen with a given colour.
void queen(display *d, int x, int y, int rgba);

//Draws a gold pawn to indicate a selected piece.
void drawSelect(display *d, int x, int y);

// Change the drawing colour.
void colour(display *d, int rgba);

// Pause for the given number of milliseconds.
void pause(display *d, int ms);

// Clear the display to white.
void clear(display *d);

// Wait for a key press.
char key(display *d);

//Returns a pointer to an int array where a[0]=x, a[1]=y.
int *mouse(display *d);

// Hold the display for a few seconds, then shut down.
void end(display *d);
