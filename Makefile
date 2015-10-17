CXX = g++
CXXFLAGS = -Wall -std=c++11 -ggdb
SRC = lisp.cpp printer.cpp parser.cpp eval.cpp main.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRC))

all: cisl

cisl: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm *.o cisl
