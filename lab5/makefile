CC=gcc
GSL_HOME=/usr/local/include/gsl

CFLAGS=-I$(GSL_HOME)/include
LDFLAGS=-L$(GSL_HOME)/lib -lgsl -lgslcblas -lm 

all: lab5

lab5: lab5.c
	$(CC) -g -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o
