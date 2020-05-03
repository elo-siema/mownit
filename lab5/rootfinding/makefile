CC=gcc
GSL_HOME=/usr/local/include/gsl

CFLAGS=-I$(GSL_HOME)/include
LDFLAGS=-L$(GSL_HOME)/lib -lgsl -lgslcblas -lm 


all: root_finding root_finding_fdf
root_finding: demo_fn.o root_finding.o
	$(CC) -g -o $@ $^ $(LDFLAGS) 

root_finding_fdf: demo_fn.o root_finding_fdf.o
	$(CC) -g -o $@ $^ $(LDFLAGS) 

