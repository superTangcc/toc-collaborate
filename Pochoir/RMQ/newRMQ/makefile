FLAG = -O3 -DNDEBUG -fomit-frame-pointer -funroll-loops

all: testRMQ

testRMQ: testRMQ.cpp RMQ_n_1_improved.o RMQ_nlogn_1.o
	g++ $(FLAG) testRMQ.cpp -o testRMQ RMQ_nlogn_1.o RMQ_n_1_improved.o

RMQ_n_1_improved.o: RMQ_n_1_improved.cpp RMQ_n_1_improved.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_n_1_improved.cpp

RMQ_nlogn_1.o: RMQ_nlogn_1.cpp RMQ_nlogn_1.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_nlogn_1.cpp
