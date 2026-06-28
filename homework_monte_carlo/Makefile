CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o mc.o

.PHONY: all clean

all: main circle_errors.txt quasi_errors.txt singular_results.txt circle_errors.svg quasi_errors.svg

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc mc.h
	$(CXX) $(CXXFLAGS) -c main.cc

mc.o: mc.cc mc.h
	$(CXX) $(CXXFLAGS) -c mc.cc

circle_errors.txt: main
	./main A_circle > circle_errors.txt

quasi_errors.txt: main
	./main B_quasi > quasi_errors.txt

singular_results.txt: main
	./main B_singular > singular_results.txt

circle_errors.svg: circle_errors.txt plot_circle_errors.gpi
	gnuplot plot_circle_errors.gpi

quasi_errors.svg: quasi_errors.txt quasi_errors.gpi
	gnuplot quasi_errors.gpi

clean:
	rm -f *.o main circle_errors.txt quasi_errors.txt singular_results.txt circle_errors.svg quasi_errors.svg