set terminal svg size 800,600 background rgb "white"
set output "wavefunctions.svg"

set xlabel "r"
set ylabel "f(r)"
set title "Lowest hydrogen s-wave eigenfunctions"
set grid

plot "wf0.txt" using 1:2 with lines title "k=0", \
     "wf1.txt" using 1:2 with lines title "k=1", \
     "wf2.txt" using 1:2 with lines title "k=2"

