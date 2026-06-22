set terminal svg size 800,600 background rgb "white"
set output "wavefunctions.svg"

set xlabel "r [Bohr radii]"
set ylabel "f(r)"
set title "Lowest hydrogen s-wave eigenfunctions"
set grid

# Exact reduced radial wavefunctions
f1(r) = 2*r*exp(-r)
f2(r) = r*(2-r)*exp(-r/2)/(2*sqrt(2))
f3(r) = 2*r*(27-18*r+2*r**2)*exp(-r/3)/(81*sqrt(3))

plot "wf0.txt" using 1:2 with lines title "Numerical n=1", \
     f1(x) with lines dashtype 2 title "Exact n=1", \
     "wf1.txt" using 1:2 with lines title "Numerical n=2", \
     f2(x) with lines dashtype 2 title "Exact n=2", \
     "wf2.txt" using 1:2 with lines title "Numerical n=3", \
     f3(x) with lines dashtype 2 title "Exact n=3"

