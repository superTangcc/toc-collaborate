CC = icc
CFLAGS = -Wall -O2 -g -lm -lpthread
DFLAGS = -Wall -O3 -xHost -unroll-aggressive -funroll-loops  -fp-model precise -g -lm -lpthread
DEBUGFLAGS = -Wall -O0 -g -lm -lpthread

matrix-cal: matrix-cal.c matrix-cal.h 
	$(CC) matrix-cal.c -o matrix-cal $(DFLAGS)
clean:
	rm -f matrix-cal *.o
