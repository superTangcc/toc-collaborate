FLAG = -O3 -DNDEBUG -fomit-frame-pointer -funroll-loops

all: testWordSA

testWordSA: testWordSA.cpp wordSA.o sa_for_ints_larsson.o RMQ_n_1_alstrup.o
	g++ $(FLAG) testWordSA.cpp -o testWordSA wordSA.o sa_for_ints_larsson.o RMQ/RMQ_n_1_alstrup.o RMQ/RMQ_nlogn_1.o

wordSA.o: wordSA.cpp wordSA.hpp sa_for_ints_larsson.hpp RMQ/RMQ_n_1_alstrup.hpp
	g++ $(FLAG) -c wordSA.cpp

sa_for_ints_larsson.o: sa_for_ints_larsson.cpp sa_for_ints_larsson.hpp
	g++ $(FLAG) -c sa_for_ints_larsson.cpp

RMQ_n_1_alstrup.o:
	(cd RMQ; make)
