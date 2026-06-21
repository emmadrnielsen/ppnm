CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wpedantic -O2

all: main

main: main.o minimization.o
	$(CXX) $(CXXFLAGS) main.o minimization.o -o main

main.o: main.cc minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

minimization.o: minimization.cc minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c minimization.cc

run: main
	./main

clean:
	rm -f main main.o minimization.o