CXX = clang++
CXXFLAG = -Wall -std=c++11
SRC = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRC))

all: cisl

cisl: $(OBJS) main.o
	$(CXX) $(CXXFLAG) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAG) -c $^ -o $@

.PHONY: clean test
clean:
	rm -f $(OBJS) cisl test main.o t/test.o

test: $(OBJS) t/test.o
	$(CXX) $(CXXFLAG) $^ -o $@ ;\
	./test                     ;\
	rm -f $(OBJS) cisl test main.o t/test.o
