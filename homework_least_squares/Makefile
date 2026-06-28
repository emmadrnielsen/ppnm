
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

all: results.txt plot.svg uncertaintiesplot.svg

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cc linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

results.txt decay_data.txt decay_fit.txt decay_band.txt: main
	./main > results.txt

plot.svg: plot.gp decay_data.txt decay_fit.txt
	gnuplot plot.gp

uncertaintiesplot.svg: uncertaintiesplot.gp decay_data.txt decay_band.txt
	gnuplot uncertaintiesplot.gp

.PHONY: all clean

clean:
	rm -f *.o main results.txt decay_data.txt decay_fit.txt decay_band.txt plot.svg uncertaintiesplot.svg