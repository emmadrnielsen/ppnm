To rebuild the program and regenerate all data files and plots:
make clean
make

Code explanations are written as comments in the code. 
AI was used for help with coding in general. 

The different tasks are 
./main A 
./main B 
./main debug   this is the coefficient comparison for task B
./main C 

To regenerate files and plots the following is done (in the Makefile)
./main A > data_A.txt
gnuplot plot.gpi

./main B > data_B.txt
gnuplot plot_qspline.gpi

./main C > data_C.txt
gnuplot plot_C.gpi


Task A:
Tests linear interpolation on cos(x). It prints z, the linear interpolation,
the integral of the linear interpolation, cos(z), and sin(z).

Task B:
Tests the quadratic spline class. It prints the spline value, derivative,
integral, and compares them with cos(z), -sin(z), and sin(z).

debug:
Checks the quadratic spline coefficients b and c for simple functions
y = 1, y = x, and y = x^2. These are compared with known expected values.

Task C:
I chose the functional programming option instead of implementing
the cubic spline.
It tests a functional version of the quadratic spline, where make_qspline
returns a function that can be evaluated as f(z).

The function make_qspline creates the same quadratic spline as in task B,
but instead of storing the spline data in a struct, it returns a function.
The vectors x, y, b and c are moved into the lambda capture, so the returned
function contains all the data it needs to evaluate the spline later.

This means that after calling

    auto f = make_qspline(x,y);

the spline can be evaluated simply as

    f(z);

Task C is run with

    ./main C

and the output is saved in data_C.txt by the Makefile.


interp.h declares the interpolation functions, the qspline struct,
and the make_qspline function.

interp.cc implements linear interpolation, the integral of the linear
interpolation, the quadratic spline, and the functional quadratic spline.

main.cc contains the tests for tasks A, B, debug, and C.
