SRCS = utils.cc timer.cc serial.cc \
	optMM.cc ompMM.cc ompMF.cc pthreadMM.cc
OBJS = $(SRCS:.cc=.o)

MATRIX_SIZE = 200

## turn on when benchmarking, otherwise use -g for debugging
OPT_FLAG = -O2
##OPT_FLAG = -g

CC = gcc
CXX = g++

.SUFFIXES: .c .o
.c.o:
	$(CC) $(OPT_FLAG) -fopenmp -pthread -c -o $@ $<
.cc.o:
	$(CXX) $(OPT_FLAG) -fopenmp -pthread -c -o $@ $<

default: hw2-p1 hw2-p2 hw2-p3 hw2-p4
all: default runtest

hw2-p1: hw2-p1.o $(OBJS)
	$(CXX) -lpthread -fopenmp -o $@ $^ -lm

hw2-p2: hw2-p2.o $(OBJS)
	$(CXX) -lpthread -fopenmp -o $@ $^ -lm

hw2-p3: hw2-p3.o $(OBJS)
	$(CXX) -lpthread -fopenmp -o $@ $^ -lm

hw2-p4: hw2-p4.o $(OBJS)
	$(CXX) -lpthread -fopenmp -o $@ $^ -lm

runtest: default
	./hw2-p1 $(MATRIX_SIZE)
	./hw2-p2 $(MATRIX_SIZE)
	./hw2-p3 $(MATRIX_SIZE)
	./hw2-p4 $(MATRIX_SIZE)

clean:
	/bin/rm -f *.o hw2-p1 hw2-p2 hw2-p3 hw2-p4

squeaky: clean
	/bin/rm -f *~
