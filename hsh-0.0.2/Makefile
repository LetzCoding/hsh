# Makefile
CC= gcc
PREFLAGS= -E -lpthread
COMPILEFLAGS= -S -lpthread 
ASFLAGS= 
ASSEMBLER= as
install:
	$(CC) $(PREFLAGS) main.c -o main.i
	$(CC) $(COMPILEFLAGS) main.i -o main.s
	$(ASSEMBLER) main.s -o hsh.o
	$(CC) hsh.o -o hsh
	make clean
remove:
	rm -f hsh
clean: main.i main.s hsh.o
	rm -f main.i main.s hsh.o
