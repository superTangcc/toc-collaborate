CFLAGS=-std=c99 -g -Wall -Werror -Wextra -coverage
testbag: bag.o
bag.o: bag.c bag.h
clean:
	rm -f *.o testbag

tar:
	(cd ..;tar cf - bag/{Makefile,bag.c,bag.h,bags.pdf,testbag.c,README} > bag/bag.tar)
