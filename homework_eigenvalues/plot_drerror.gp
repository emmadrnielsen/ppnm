set terminal svg size 800,600
set output "plot_drerror.svg"
set terminal svg background rgb "white"

set xlabel "dr"
set ylabel "|e0 + 0.5|"
set title "Convergence of ground-state energy"
set grid

plot "dr_data.txt" using 1:(abs($2 + 0.5)) with linespoints title "Error"