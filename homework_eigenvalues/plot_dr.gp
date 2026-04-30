set terminal svg size 800,600
set output "plot_dr.svg"
set terminal svg background rgb "white"

set xlabel "dr"
set ylabel "Ground state energy e0"
set title "Convergence with respect to dr"
set grid

plot "dr_data.txt" using 1:2 with linespoints title "Numerical e0"