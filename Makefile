CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -O3 -I$(EIG_DIR) -I$(SPECTRA_DIR)

OBJECTS = main.o LaplacePeriodicGrid2D.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): Point.h PeriodicGrid2D.h
