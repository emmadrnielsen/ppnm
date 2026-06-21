CXX = clang++
CXXFLAGS += -std=c++23 -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

# all: Out.txt
# 		cat $<

# Out.txt : main
# #		./main > Out.txt
# 		./$< > $@

.PHONY: all clean

all: main

main: main.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

main.o: main.cc linalg.h

out.times.data: main 
	> $@
	for N in $$(seq 200 100 1000); do \
		/usr/bin/time --format "$$N %e" --output $@ --append \
		./$< C $$N > /dev/null 2>>err ; \
	done 

clean:
	rm -f main *.o out.times.data err
