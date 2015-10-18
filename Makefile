CXX = g++
CXXFLAGS = -Wall -std=c++11 -ggdb
SRC = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRC))

all: cisl

cisl: $(OBJS) src/init.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

src/init.o: src/init.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	
src/init.cpp:
	cat src/lib/header.txt $(wildcard src/lib/*.cpp) src/lib/footer.txt > src/init.cpp

.PHONY: clean
clean:
	rm -f $(OBJS) cisl src/init.cpp core
