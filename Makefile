CXX = g++
CXXFLAGS = -std=c++0x -Wall

OBJECTS = Point_test.o Point.o

Point_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): Point.hpp
