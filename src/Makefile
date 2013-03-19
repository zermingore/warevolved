CC = gcc
FLAGS = -W -Wall -Werror -ansi -pedantic -O2
FILES = $(wildcard *.c)#init.c error.c debug.c grid.c
LIBFLAGS = -lSDL
EXE = we

all:
	$(CC) $(FLAGS) $(LIBFLAGS) $(FILES) -o $(EXE)

