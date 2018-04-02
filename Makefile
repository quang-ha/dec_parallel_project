CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -I$(EIG_DIR) -I$(SPECTRA_DIR)

OBJECTS = main.o Point.o Grid2D.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): Point.h Grid2D.h
