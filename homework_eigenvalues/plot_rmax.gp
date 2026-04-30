set terminal svg size 800,600
set output "plot_rmax.svg"
set terminal svg background rgb "white"

set xlabel "rmax"
set ylabel "Ground state energy e0"
set title "Convergence with respect to rmax"
set grid

plot "rmax_data.txt" using 1:2 with linespoints title "Numerical e0"