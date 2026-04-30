
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc linalg.h 
	$(CXX) $(CXXFLAGS) -c main.cc

clean:
	rm -f *.o main