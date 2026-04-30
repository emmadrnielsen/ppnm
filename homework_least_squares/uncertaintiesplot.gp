set terminal svg size 800,600
set output "uncertaintiesplot.svg"
set terminal svg background rgb "white"

plot "decay_data.txt" using 1:2:3 with yerrorbars title "data", \
     "decay_band.txt" using 1:2 with lines title "best fit", \
     "decay_band.txt" using 1:3 with lines title "+ +", \
     "decay_band.txt" using 1:4 with lines title "+ -", \
     "decay_band.txt" using 1:5 with lines title "- +", \
     "decay_band.txt" using 1:6 with lines title "- -"
