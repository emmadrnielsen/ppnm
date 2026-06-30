CXX = g++
CXXFLAGS = -std=c++23 -O2 -Wall -Wextra -pedantic

all: main A1_txt A2_txt network.png B_txt derivatives.png C_txt ode_network.png

main: main.o neural.o minimization.o
	$(CXX) $(CXXFLAGS) -o main main.o neural.o minimization.o

main.o: main.cc neural.h minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

neural.o: neural.cc neural.h minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c neural.cc

minimization.o: minimization.cc minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c minimization.cc


A1_txt: main
	./main A1 > A1_txt


A2_txt network.data training.data: main
	./main A2 > A2_txt 2>&1

network.png: network.data training.data
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


B_txt derivatives.data: main
	./main B > B_txt 2>&1

derivatives.png: derivatives.data
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


C_txt ode_network.data: main
	./main C > C_txt 2>&1

ode_network.png: ode_network.data
	gnuplot -e "\
	set terminal pngcairo size 900,1000; \
	set output 'ode_network.png'; \
	set multiplot layout 3,1; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	plot 'ode_network.data' using 1:2 with lines linewidth 3 title 'exact sin(x)', \
	     'ode_network.data' using 1:3 with points pointtype 7 pointsize 0.4 title 'network'; \
	set ylabel 'network - exact'; \
	plot 'ode_network.data' using 1:(\$$3-\$$2) with lines title 'F(x)-sin(x)'; \
	set ylabel 'residual'; \
	plot 'ode_network.data' using 1:4 with lines title \"F''(x)+F(x)\"; \
	unset multiplot"


plot: network.png

plotB: derivatives.png

plotC: ode_network.png


clean:
	rm -f main *.o \
	      A1_txt A2_txt B_txt C_txt \
	      network.data training.data network.png \
	      derivatives.data derivatives.png \
	      ode_network.data ode_network.png

.PHONY: all clean plot plotB plotC