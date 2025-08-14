# define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# define libraries to be linked (for example -lm)
LIB = 

# define sets of header source files and object files
SRC = driver.c in-out.c data.c 
# OBJ is the same as SRC, just replace .c with .h
OBJ = $(SRC:.c=.o)
 
# define the executable name(s)
EXE = ass1

# the first target:
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LIB)

driver.o: driver.c data.h in-out.h

data.o: data.c data.h

in-out.o: in-out.c in-out.h data.h

clean:
	rm -f $(OBJ) $(EXE)