set terminal png
set output "running_time.png"

set title "Parallel Harmonic Sum Performance"
set xlabel "Number of threads"
set ylabel "Running time (seconds)"

set grid

plot "out.times" using 1:2 with linespoints title "real time"