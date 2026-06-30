
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o jacobi.o hydrogen.o

.PHONY: all clean make_A make_B plot_B make_convergence plot_convergence make_C scaling plot_C

all: make_A plot_B plot_convergence plot_C

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc jacobi.h linalg.h hydrogen.h
	$(CXX) $(CXXFLAGS) -c main.cc

jacobi.o: jacobi.cc jacobi.h linalg.h
	$(CXX) $(CXXFLAGS) -c jacobi.cc

hydrogen.o: hydrogen.cc hydrogen.h linalg.h
	$(CXX) $(CXXFLAGS) -c hydrogen.cc


.PHONY: make_A

make_A: main 
	./main A | tee task_A.txt

.PHONY: make_B

make_B: main
	./main B -rmax 30 -dr 0.2 | tee task_B.txt

.PHONY: plot_B

plot_B: make_B
	gnuplot plot_wf.gp

.PHONY: plot_convergence

dr_data.txt rmax_data.txt: main
	./main Bconvergence | tee task_Bconvergence.txt

plot_convergence: dr_data.txt rmax_data.txt
	gnuplot plot_dr.gp
	gnuplot plot_drerror.gp
	gnuplot plot_rmax.gp
	gnuplot plot_rmaxerror.gp

Ns = 40 60 80 100 120 140 160 180

.PHONY: scaling plot_C

scaling_data.txt: main
	> scaling_data.txt
	for N in $(Ns); do ./main C $$N >> scaling_data.txt; done

scaling: scaling_data.txt

plot_C: scaling_data.txt
	gnuplot plot_C.gp

clean:
	rm -f *.o main
	rm -f task_A.txt task_B.txt task_Bconvergence.txt
	rm -f wf0.txt wf1.txt wf2.txt
	rm -f dr_data.txt rmax_data.txt scaling_data.txt
	rm -f wavefunctions.svg plot_dr.svg plot_drerror.svg plot_rmax.svg plot_rmaxerror.svg scaling.svg
	rm -f fit.log fit_C.log




