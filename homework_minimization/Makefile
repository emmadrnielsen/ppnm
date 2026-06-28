CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wpedantic -O2

.PHONY: all clean run

# 1. The default 'all' target now demands the executable AND all the outputs
all: main A1.txt A2.txt A3.txt C.txt fit.data.txt higgs.svg

main: main.o minimization.o
	$(CXX) $(CXXFLAGS) main.o minimization.o -o main

main.o: main.cc minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

minimization.o: minimization.cc minimization.h linalg.h
	$(CXX) $(CXXFLAGS) -c minimization.cc

# --- Rules for generating the output files ---

A1.txt: main
	./main A1 > A1.txt

A2.txt: main
	./main A2 > A2.txt

A3.txt: main
	./main A3 > A3.txt

C.txt: main
	./main C > C.txt

# This rule runs the fit and generates both fit.data.txt and fit.log
fit.data.txt: main higgs.data.txt
	./main B < higgs.data.txt > fit.data.txt 2> fit.log

# The plot depends on the gnuplot script and the generated fit data
higgs.svg: higgs.gpi fit.data.txt higgs.data.txt
	gnuplot higgs.gpi

run: main
	./main

# 2. 'clean' now completely wipes the slate clean
clean:
	rm -f main main.o minimization.o A1.txt A2.txt A3.txt C.txt fit.data.txt fit.log higgs.svg