OBJS = $(wildcard */*.c)
CC = gcc
INCLUDE_PATHS = -I/opt/homebrew/opt/sdl2/include 
# -I/opt/homebrew/opt/sdl2_mixer/include -D_THREAD_SAFE
LIBRARY_PATHS = -L/opt/homebrew/opt/sdl2/lib 
# -L/opt/homebrew/opt/sdl2_mixer/lib
COMPILER_FLAGS = -Wall -g -std=c17
LINKER_FLAGS = -lSDL2
# OBJ_Name = newCube
# when OBJ_Name = main is changed, that is git the change in the source file.
OBJ_NAME = main

# gcc -Wall -g -std=c99 -I/opt/homebrew/opt/sdl2/include -L/opt/homebrew/opt/sdl2/lib ./src/*.c -o main -lSDL2
#  ./main
all:
	$(CC) -o $(OBJ_NAME) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OBJS)
