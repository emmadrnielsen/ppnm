CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS)
LDLIBS = -lstdc++ -lm 

Out.txt: main
	./main > Out.txt

main.o: hello.h sfuns.h
hello.o: hello.h
sfuns.o: sfuns.h
main: main.o hello.o sfuns.o

#	$(CXX) main.o hello.o sfuns.o -o main $(LDLIBS)
#	$(CXX) $^ -o main $(LDLIBS) # This does the same as above

#main.o : hello.h sfuns.h main.cc
#		$(CXX) $(CXXFLAGS) -c main.cc -o main.o

#hello.o: hello.h hello.cc
#		$(CXX) $(CXXFLAGS) -c hello.cc -o hello.o

#sfuns.o: sfuns.h sfuns.cc
#		$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o

.PHONY: clean
clean:
	$(RM) main main.o hello.o Out.txt


test: 
		@echo CXX
		@echo $(CXX)
		@echo $(RM)