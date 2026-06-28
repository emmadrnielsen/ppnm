CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

all: A_debug.txt A_rosenbrock.txt A_himmelblau.txt B.txt hydrogen.svg convergence_rmax.svg convergence_rmin.svg convergence_acc.svg convergence_eps.svg

main: main.o roots.o ode.o
	$(CXX) $(CXXFLAGS) -o main main.o roots.o ode.o

main.o: main.cc roots.h ode.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

roots.o: roots.cc roots.h linalg.h
	$(CXX) $(CXXFLAGS) -c roots.cc

ode.o: ode.cc ode.h linalg.h
	$(CXX) $(CXXFLAGS) -c ode.cc

A_debug.txt: main
	./main A_debug > A_debug.txt

A_rosenbrock.txt: main
	./main A_rosenbrock > A_rosenbrock.txt

A_himmelblau.txt: main
	./main A_himmelblau > A_himmelblau.txt

B.txt hydrogen.data: main
	./main B > B.txt

convergence_rmax.data convergence_rmin.data convergence_acc.data convergence_eps.data: main
	./main B2

hydrogen.svg: hydrogen.data plot_hydrogen.gpi
	gnuplot plot_hydrogen.gpi

convergence_rmax.svg convergence_rmin.svg convergence_acc.svg convergence_eps.svg: convergence_rmax.data convergence_rmin.data convergence_acc.data convergence_eps.data plot_convergence.gpi
	gnuplot plot_convergence.gpi

clean:
	rm -f main *.o *.txt *.data *.svg