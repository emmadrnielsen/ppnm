CXX = clang++
CXXFLAGS += -std=c++23 -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

# all: Out.txt
# 		cat $<

# Out.txt : main
# #		./main > Out.txt
# 		./$< > $@

.PHONY: all clean

all: Task_A.txt Task_B.txt QR_runtime.svg

Task_A.txt: main
	./main A > $@

Task_B.txt: main
	./main B > $@

out.times.data: main
	> $@
	for N in $$(seq 200 100 1000); do \
		/usr/bin/time --format "$$N %e" --output $@ --append \
		./$< C $$N > /dev/null 2>>err ; \
	done

QR_runtime.svg: out.times.data plot_C.gpi
	gnuplot plot_C.gpi

clean:
	rm -f main *.o Task_A.txt Task_B.txt out.times.data QR_runtime.svg err fit.log
