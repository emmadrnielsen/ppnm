CXX = clang++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<

Out.txt : main
#		./main > Out.txt
		./$< > $@

main: main.o hello.o vec.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

main.o: main.cc vec.h hello.h
hello.o: hello.cc hello.h
vec.o: vec.cc vec.h

clean:
	rm -f main *.o Out.txt
