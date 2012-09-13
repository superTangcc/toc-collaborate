CPPOPTS = -O3 -g -Wall
CC = g++
#CC = icc
#INTEL_CXX = icpc

TARGET = tbb_stencil.exe tbb_stencil_vec.exe
OBJS = tbb_stencil.o  tbb_stencil_vec.o
HEADER = util_time.h
LIBS = -ltbb

all:	$(TARGET)

tbb_stencil.exe: tbb_stencil.o 
	$(CC) $(CPPOPTS) -o $@ $< $(LIBS)

tbb_stencil_vec.exe: tbb_stencil_vec.o
	$(CC) $(CPPOPTS) -o $@ tbb_stencil_vec.o $(LIBS)

$(OBJS):%.o: %.cpp $(HEADER)
	$(CC) $(CPPOPTS) -I. -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

