BIN = sudoku s
OBJECTS= sudoku.o s.o
CC = gcc
CFALGS = -Wall -g -pthread
.PHONY : sudoku s          
sudoku :
	gcc -o sudoku sudoku.c -lpthread
s :
	gcc -o s sort.c -lpthread
clean :
	rm -f $(OBJECTS) $(BIN) no_sort.txt
