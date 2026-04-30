CXX = clang++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<

Out.txt : main
#		./main > Out.txt
		./$< > $@

main.o: approx.h
approx.o: approx.h
main: main.o approx.o