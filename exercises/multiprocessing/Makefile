all: plot

main: main.cc
	g++ -O3 -std=c++17 -pthread main.cc -o main

out.times: main
	> out.times
	> log.main
	for nthreads in 1 2 3 4 5 6 7 8; do \
		echo -n "$$nthreads " >> out.times; \
		time --format "%e %U" --append --output out.times \
		./main -nthreads $$nthreads -nterms 1000000000 >> log.main; \
	done

plot: out.times plot.gp
	gnuplot plot.gp

clean:
	rm -f main out.times log.main running_time.png