
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o integrate.o

all: main A2_tests.txt erf_data.txt erf.svg erf_convergence.txt erf_convergence.svg B2compare.txt infinite_tests.txt error_estimate.txt pythoncompare.txt pythoncompare_infinite.txt

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc integrate.h
	$(CXX) $(CXXFLAGS) -c main.cc

integrate.o: integrate.cc integrate.h
	$(CXX) $(CXXFLAGS) -c integrate.cc

A2_tests.txt: main
	./main A2 > A2_tests.txt

erf_data.txt: main
	./main A3 > erf_data.txt

erf_convergence.txt: main
	./main A4 > erf_convergence.txt

B2compare.txt: main
	./main B2 > B2compare.txt

infinite_tests.txt: main
	./main B4 > infinite_tests.txt

error_estimate.txt: main
	./main C > error_estimate.txt

pythoncompare.txt: compare_scipy.py
	python3 compare_scipy.py > pythoncompare.txt

pythoncompare_infinite.txt: compare_scipy_infinite.py
	python3 compare_scipy_infinite.py > pythoncompare_infinite.txt

erf.svg: erf_data.txt plot_erf.gpi
	gnuplot plot_erf.gpi

erf_convergence.svg: erf_convergence.txt plot_erf_convergence.gpi
	gnuplot plot_erf_convergence.gpi

GENERATED = A2_tests.txt erf_data.txt erf_convergence.txt \
            B2compare.txt infinite_tests.txt error_estimate.txt \
            pythoncompare.txt pythoncompare_infinite.txt \
            erf.svg erf_convergence.svg

.PHONY: all clean

clean:
	rm -f $(OBJS) main $(GENERATED)