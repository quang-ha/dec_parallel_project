CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3

OBJECTS = main.o Point.o Grid2D.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): Point.h Grid2D.h
