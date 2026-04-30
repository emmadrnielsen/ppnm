
CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

all: fig1.svg fig2.svg fig3.svg

main: main.cc

erf.data: main
	./main erf > $@

gamma.data: main
	./main gamma > $@ 2> factorial.data

lngamma.data: main
	./main lngamma > $@ 2> logfactorial.data

fig1.svg: fig1.gpi erf.data
	gnuplot $<

fig2.svg: fig2.gpi gamma.data factorial.data
	gnuplot $<

fig3.svg: fig3.gpi lngamma.data logfactorial.data
	gnuplot $<

clean:
	rm -f main erf.data gamma.data factorial.data lngamma.data logfactorial.data fig1.svg fig2.svg fig3.svg