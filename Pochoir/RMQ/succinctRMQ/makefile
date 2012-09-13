FLAG = -O2 -fomit-frame-pointer -funroll-loops

all: testRMQ

testRMQ: testRMQ.cpp RMQ_1_n.o RMQ_succinct.o
	g++ $(FLAG) testRMQ.cpp -o testRMQ  RMQ_1_n.o RMQ_succinct.o

RMQ_succinct.o: RMQ_succinct.cpp RMQ_succinct.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_succinct.cpp

RMQ_1_n.o: RMQ_1_n.cpp RMQ_1_n.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_1_n.cpp
