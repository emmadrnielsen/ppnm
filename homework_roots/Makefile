main: main.o roots.o ode.o
	$(CXX) $(CXXFLAGS) -o main main.o roots.o ode.o

main.o: main.cc roots.h ode.h linalg.h
	$(CXX) $(CXXFLAGS) -c main.cc

roots.o: roots.cc roots.h linalg.h
	$(CXX) $(CXXFLAGS) -c roots.cc

ode.o: ode.cc ode.h linalg.h
	$(CXX) $(CXXFLAGS) -c ode.cc

clean:
	rm -f main *.o hydrogen.data