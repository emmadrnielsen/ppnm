
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o jacobi.o hydrogen.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc jacobi.h linalg.h hydrogen.h
	$(CXX) $(CXXFLAGS) -c main.cc

jacobi.o: jacobi.cc jacobi.h linalg.h
	$(CXX) $(CXXFLAGS) -c jacobi.cc

hydrogen.o: hydrogen.cc hydrogen.h linalg.h
	$(CXX) $(CXXFLAGS) -c hydrogen.cc

clean:
	rm -f *.o main




