This is a working game of checkers, unfinished, but functional. The program is written so that any size board can be played, by simply changing "b->size" in the "game" module.

To compile, type "make play" and it will link all 4 modules together. They structure of the program is such that the "play" module relies on the other three modules, "logic" relies on "game" and "display" and "game" only relies on "display", which relies on the SDL library. I have tried to avoid library clashes/repeats.

The "play" module sets up the game and displays it, the "logic" module contains most of the code and all of the logic of the game and moving pieces, the "game" module sets up the structures and links the "square" structures together, and the "display" module is similar to that in the sketch assignment, with added functions to draw pawns and queens.

The board is a structure which consists of an AxA mesh of "square" structs; each square is its own structure with various properties. I chose to do this to make the logic of the game more readable. Each square links to it's adjacent squares (top, bottom, left, right).

I also added a feature where selecting each piece changes the colour, and that the game recognises when you want to change the piece you wish to move. The board is displayed such that it does not have to be redrawn after every move, only the squares that have been changed need to be redrawn.

The game is unfinished in terms of logic but the work required is minimal in difficulty but is more time consuming, and with the upcoming January exams I did not manage to find the time to bugfix to completion. The code needed to be added works on the functions that are already in place however, so any other developer could add them with relative ease.





The program is inside the ZIP file I included, and to re-iterate, type "make play" and "./play" in the terminal to run the game.
