set terminal svg size 800,600 background rgb "white"
set output "scaling.svg"

set xlabel "Matrix size N"
set ylabel "Diagonalization time [s]"
set title "Scaling of Jacobi diagonalization"
set grid
set logscale x
set logscale y

# Fit time = a*N^b. For O(N^3), b should be close to 3.
a = 1e-7
b = 3.0

f(x) = a*x**b
set fit logfile "fit_C.log"
fit f(x) "scaling_data.txt" using 1:2 via a,b

plot "scaling_data.txt" using 1:2 with linespoints \
         title "Measured time", \
     f(x) with lines dashtype 2 \
         title sprintf("Fit: N^{%.2f}", b)