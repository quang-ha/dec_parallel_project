CXX = g++
CXXFLAGS = -fPIC -g -std=c++11 -Wall -O3 -ffast-math -I$(HOME)/EigenSpectra/SpectraSrc/include -fopenmp

OBJECTS = main.o LaplacePeriodicGrid2D.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): Point.h PeriodicGrid2D.h
