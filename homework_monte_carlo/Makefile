CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o mc.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc mc.h
	$(CXX) $(CXXFLAGS) -c main.cc

mc.o: mc.cc mc.h
	$(CXX) $(CXXFLAGS) -c mc.cc

clean:
	rm -f *.o main 