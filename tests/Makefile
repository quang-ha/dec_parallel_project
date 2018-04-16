CC=g++
CXXFLAGS=-std=c++11 -O3 -Wall

DEPS = ../PeriodicGrid2D.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $@ $<

all: pg2dtest

clean:
	rm -rf *o pg2dtest
