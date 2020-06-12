CC=g++
GSL_HOME=/usr/local/include/gsl

CFLAGS=-I$(GSL_HOME)/include
LDFLAGS=-L$(GSL_HOME)/lib -lgsl -lgslcblas -lm 

all: main

lab6: main.c
	gcc -g -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
