GFLAGS=-Wall -g -O2 -std=gnu99

EXE=program

SRC=./src

CODE ./memroy/instruction.c ./disk/code.c

.PHONY:program
main:
	gcc $(GFLAGS) -I $(SRC) $(CODE) -o $(EXE)

run:
./$(EXE)
