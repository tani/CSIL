CXX = g++
CXXFLAG = -Wall -std=c++11
SRC = $(wildcard src/*.cpp) src/init.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRC))

all: cisl

cisl: $(OBJS) main.o
	$(CXX) $(CXXFLAG) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAG) -c $^ -o $@

main.o:
	$(CXX) $(CXXFLAG) -c main.cpp -o $@

src/init.cpp:
	cat src/lib/header.txt $(wildcard src/lib/*.cpp) src/lib/footer.txt > src/init.cpp

.PHONY: clean test
clean:
	rm -f $(OBJS) cisl src/init.cpp core t/test.o test main.o

test: t/test.o $(OBJS)
	$(CXX) $(CXXFLAG) $^ -o $@

t/test.o:
	$(CXX) $(CXXFLAG) -c t/test.cpp -o $@
