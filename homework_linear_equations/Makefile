CXX = clang++
CXXFLAGS += -std=c++23 -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<

Out.txt : main
#		./main > Out.txt
		./$< > $@

main: main.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

main.o: main.cc linalg.h

out.times.data: main # virker pt ikke lige 
	> $@
	for N in $$(seq 100 20 200); do \
		/usr/bin/time --format "$$N %e" --output $@ --append \
		./$< $$N > /dev/null 2>>err ; \
	done 

clean:
	rm -f main *.o Out.txt
