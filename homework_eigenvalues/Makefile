
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

.PHONY: plot_B

plot_B:
	gnuplot plot_wf.gp

.PHONY: plot_convergence

dr_data.txt rmax_data.txt: main
	./main Bconvergence

plot_convergence: dr_data.txt rmax_data.txt
	gnuplot plot_dr.gp
	gnuplot plot_drerror.gp
	gnuplot plot_rmax.gp
	gnuplot plot_rmaxerror.gp

Ns = 20 30 40 50 60 70 80

.PHONY: scaling plot_C

scaling_data.txt: main
	> scaling_data.txt
	for N in $(Ns); do ./main C $$N >> scaling_data.txt; done

scaling: scaling_data.txt

plot_C: scaling_data.txt
	gnuplot plot_C.gp

clean:
	rm -f *.o main




