CC=gcc
GSL_HOME=/usr/local/include/gsl

CFLAGS=-I$(GSL_HOME)/include
LDFLAGS=-L$(GSL_HOME)/lib -lgsl -lgslcblas -lm 

all: approx

approx: approx.c
	$(CC)  -o $@ $^ $(LDFLAGS)

zad2: zad2.c
	$(CC)  -g -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o
