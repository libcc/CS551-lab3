CC=gcc
DEBUG=-g

pipesort: pipesort.o
	$(CC) $(DEBUG) -o pipesort pipesort.o

pipesort.o: pipesort.c
	$(CC) $(DEBUG) -c pipesort.c

clean: 
	rm pipesort pipesort.o
