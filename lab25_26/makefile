CC = gcc
CFLAGS = -std=c99 -Wall -g
OBJ = lab26.o Squeue.o sort.o
PROG = l26

build: lab26.o sort.o Squeue.o
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)

lab26.o: lab26.c
	$(CC) $(CFLAGS) -c lab26.c

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c

Squeue.o: Squeue.c
	$(CC) $(CFLAGS) -c Squeue.c

clean:
	rm $(PROG) $(OBJ)
