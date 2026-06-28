CXX = g++
CXXFLAGS = -std=c++23 -O2 -Wall -Wextra -pedantic

.PHONY: all clean plot plotB plotC

all: main plot plotB plotC

main: main.o neural.o minimization.o
	$(CXX) $(CXXFLAGS) -o main main.o neural.o minimization.o

main.o: main.cc neural.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

neural.o: neural.cc neural.h minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c neural.cc

minimization.o: minimization.cc minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c minimization.cc

plot: network.data training.data
	gnuplot -e "\
	set terminal pngcairo size 900,600; \
	set output 'network.png'; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set grid; \
	plot \
	'network.data' using 1:2 with lines title 'exact', \
	'network.data' using 1:3 with lines title 'network', \
	'training.data' using 1:2 with points pointtype 7 title 'training data'"

network.data training.data: main
	./main A2

plotB: derivatives.data
	gnuplot -e "\
	set terminal pngcairo size 1000,1200; \
	set output 'derivatives.png'; \
	set multiplot layout 4,1; \
	set grid; \
	set xlabel 'x'; \
	plot 'derivatives.data' using 1:2 with lines title 'exact', \
	     'derivatives.data' using 1:3 with lines title 'network'; \
	plot 'derivatives.data' using 1:4 with lines title 'exact first derivative', \
	     'derivatives.data' using 1:5 with lines title 'network first derivative'; \
	plot 'derivatives.data' using 1:6 with lines title 'exact second derivative', \
	     'derivatives.data' using 1:7 with lines title 'network second derivative'; \
	plot 'derivatives.data' using 1:8 with lines title 'network antiderivative'; \
	unset multiplot"

derivatives.data: main
	./main B

plotC: ode_network.data
	gnuplot -e "\
	set terminal pngcairo size 900,800; \
	set output 'ode_network.png'; \
	set multiplot layout 2,1; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	plot 'ode_network.data' using 1:2 with lines title 'exact sin(x)', \
	     'ode_network.data' using 1:3 with lines title 'network'; \
	set ylabel 'residual'; \
	plot 'ode_network.data' using 1:4 with lines title \"F''(x)+F(x)\"; \
	unset multiplot"

ode_network.data: main
	./main C

clean:
	rm -f main *.o network.data training.data network.png \
	      derivatives.data derivatives.png ode_network.data ode_network.png