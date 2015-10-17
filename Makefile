CXX = g++
CXXFLAGS = -Wall -std=c++11 -ggdb
SRC = src/eval.cpp src/lisp.cpp src/main.cpp src/parser.cpp src/printer.cpp src/init.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRC))

all: cisl

cisl: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.cpp.o: src/init.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

src/init.cpp: src/lib/header.txt src/lib/footer.txt
	cat src/lib/header.txt src/lib/*.cpp src/lib/footer.txt > src/init.cpp

.PHONY: clean
clean:
	rm -f src/*.o cisl src/init.cpp core
