FLAG = -O3 -DNDEBUG -fomit-frame-pointer -funroll-loops

all: RMQ_n_1_alstrup.o RMQ_nlogn_1.o

RMQ_n_1_alstrup.o: RMQ_n_1_alstrup.cpp RMQ_n_1_alstrup.hpp RMQ_nlogn_1.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_n_1_alstrup.cpp

RMQ_nlogn_1.o: RMQ_nlogn_1.cpp RMQ_nlogn_1.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_nlogn_1.cpp
