CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -pedantic

all: main decomp_check.txt linear_check.txt determinant_check.txt inverse_check.txt

main: main.o cholesky.o
	$(CXX) $(CXXFLAGS) main.o cholesky.o -o main

main.o: main.cc cholesky.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

cholesky.o: cholesky.cc cholesky.h linalg.h
	$(CXX) $(CXXFLAGS) -c cholesky.cc

decomp_check.txt: main
	./main decomposition > decomp_check.txt

linear_check.txt: main
	./main linear > linear_check.txt

determinant_check.txt: main
	./main determinant > determinant_check.txt

inverse_check.txt: main
	./main inverse > inverse_check.txt

clean:
	rm -f main main.o cholesky.o decomp_check.txt linear_check.txt determinant_check.txt inverse_check.txt