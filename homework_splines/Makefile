
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o interp.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc interp.h
	$(CXX) $(CXXFLAGS) -c main.cc

interp.o: interp.cc interp.h
	$(CXX) $(CXXFLAGS) -c interp.cc

clean:
	rm -f *.o main data.txt plot.svg qspline_plot.svg C_functional_qspline.svg