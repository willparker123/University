# Find the OS platform using the uname command.
Linux := $(findstring Linux, $(shell uname -s))
MacOS := $(findstring Darwin, $(shell uname -s))
Windows := $(findstring NT, $(shell uname -s))

# Specify what typing 'make' on its own will compile
default: game

# For Windows, add the .exe extension
ifdef Windows

play: play.c logic.c game.c display.c
	clang -std=c11 -Wall -pedantic -g $@.c logic.c game.c display.c -lSDL2 -o $@.exe

test: logic.c game.c test.c
	clang -std=c11 -Wall -pedantic -g logic.c game.c test.c -o $@.exe

%: %.c
	clang -Dtest_$@ -std=c11 -Wall -pedantic -g $@.c -o $@.exe

# For Linux/MacOS, include the advanced debugging options
else

play: play.c
	clang -std=c11 -Wall -pedantic -g $@.c logic.c game.c display.c -lSDL2 -o $@ \
	    -fsanitize=undefined -fsanitize=address

test: logic.c game.c test.c
	clang -std=c11 -Wall -pedantic -g logic.c game.c test.c -o $@ \
	    -fsanitize=undefined -fsanitize=address

%: %.c
	clang -Dtest_$@ -std=c11 -Wall -pedantic -g $@.c -o $@ \
	    -fsanitize=undefined -fsanitize=address

endif
