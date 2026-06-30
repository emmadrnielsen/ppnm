
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o ode.o

.PHONY: all clean

all: main harmonic_oscillator.svg pendulum.svg orbit_B1.svg orbit_B2.svg orbit_B3.svg three_body_C.svg

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc ode.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

ode.o: ode.cc ode.h linalg.h
	$(CXX) $(CXXFLAGS) -c ode.cc

data.txt: main
	./main A3 > data.txt

pendulum.txt: main
	./main A4 > pendulum.txt

orbit_B1.txt: main
	./main B1 > orbit_B1.txt

orbit_B2.txt: main
	./main B2 > orbit_B2.txt

orbit_B3.txt: main
	./main B3 > orbit_B3.txt

three_body_C.txt: main
	./main C > three_body_C.txt

harmonic_oscillator.svg: data.txt plot.gpi
	gnuplot plot.gpi

pendulum.svg: pendulum.txt plot_pendulum.gpi
	gnuplot plot_pendulum.gpi

orbit_B1.svg: orbit_B1.txt plot_B1.gpi
	gnuplot plot_B1.gpi

orbit_B2.svg: orbit_B2.txt plot_B2.gpi
	gnuplot plot_B2.gpi

orbit_B3.svg: orbit_B3.txt plot_B3.gpi
	gnuplot plot_B3.gpi

three_body_C.svg: three_body_C.txt plot_C.gpi
	gnuplot plot_C.gpi

clean:
	rm -f *.o main \
	      data.txt pendulum.txt orbit_B1.txt orbit_B2.txt orbit_B3.txt three_body_C.txt \
	      harmonic_oscillator.svg pendulum.svg orbit_B1.svg orbit_B2.svg orbit_B3.svg three_body_C.svg