
CXX = g++
CXXFLAGS = -O2 -std=c++23 -Wall -Wextra -pedantic

OBJS = main.o interp.o

.PHONY: all clean

all: main data_A.txt data_B.txt data_C.txt plot.svg qspline_plot.svg C_functional_qspline.svg

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc interp.h
	$(CXX) $(CXXFLAGS) -c main.cc

interp.o: interp.cc interp.h
	$(CXX) $(CXXFLAGS) -c interp.cc

data_A.txt: main
	./main A > data_A.txt

data_B.txt: main
	./main B > data_B.txt

data_C.txt: main
	./main C > data_C.txt

plot.svg: data_A.txt plot.gpi
	gnuplot plot.gpi

qspline_plot.svg: data_B.txt plot_qspline.gpi
	gnuplot plot_qspline.gpi

C_functional_qspline.svg: data_C.txt plot_C.gpi
	gnuplot plot_C.gpi

clean:
	rm -f *.o main data_A.txt data_B.txt data_C.txt plot.svg qspline_plot.svg C_functional_qspline.svg