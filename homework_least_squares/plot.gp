set terminal svg size 800,600
set output "plot.svg"
set terminal svg background rgb "white"

set xlabel "time t (days)"
set ylabel "activity"
set title "Radioactive decay of ThX / 224Ra"
set grid
plot "decay_data.txt" using 1:2:3 with yerrorbars title "experimental data", \
     "decay_fit.txt" using 1:2 with lines title "best exponential fit"