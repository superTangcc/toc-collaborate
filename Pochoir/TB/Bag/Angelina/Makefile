CC=gcc
INCLUDES=-I. 

CFLAGS=-Wall -g -O2 $(INCLUDES)
PROG=bag_test

default: $(PROG)

main.o: main.c bag.h
	$(CC) $(CFLAGS) -c -o main.o main.c

bag.o: bag.c bag.h
	$(CC) $(CFLAGS) -c -o bag.o bag.c

bag_test: main.o bag.o 
	$(CC) $(CLAGS) -o $@ main.o bag.o 


clean::
	-rm -f $(PROG) *.o

