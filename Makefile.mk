CC=g++
CFLAGS=-I. --std=c++98 -O3
OUTPUT = output

.PHONY: all
all: clean main.o
    $(CC) $(CFLAGS) -o $(OUTPUT) $%*.o

.PHONY: clean
clean:
    rm -f *.o