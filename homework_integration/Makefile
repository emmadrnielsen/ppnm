
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o integrate.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc integrate.h
	$(CXX) $(CXXFLAGS) -c main.cc

integrate.o: integrate.cc integrate.h
	$(CXX) $(CXXFLAGS) -c integrate.cc

clean:
	rm -f *.o main