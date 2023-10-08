CC = gcc
GFLAGS=-Wall -g -O2 -std=gnu99

TARGET=csapp
#SRC_DIR=./src

CODE=./src/memory/instruction.c ./src/memory/dram.c ./src/disk/code.c ./src/cpu/mmu.c ./src/main.c

.PHONY:csapp
main:
	$(CC) $(GFLAGS) $(CODE) -o $(TARGET)
clean:
	rm -f *.o *~$(TARGET)
run:
	./$(TARGET)
