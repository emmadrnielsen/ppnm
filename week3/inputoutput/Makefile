CXX = clang++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror -O2
LDLIBS += -lstdc++ -lm

all: main-cmdline main-stdinstr main-fstreams

main-cmdline: main-cmdline.cc
	$(CXX) $(CXXFLAGS) $< -o $@

main-stdinstr: main-stdinstr.cc
	$(CXX) $(CXXFLAGS) $< -o $@

main-fstreams: main-fstreams.cc
	$(CXX) $(CXXFLAGS) $< -o $@


