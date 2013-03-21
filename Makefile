CXX=clang++
CXXFLAGS=-std=c++11 -Wall -Wextra -g

all: ts

clean:
	$(RM) ts.o civilians_and_killers.o farmer.o ts

ts: ts.o civilians_and_killers.o farmer.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

ts.o: civilians_and_killers.h farmer.h

civilians_and_killers.o farmer.o:%.o: %.h presentation.hpp state_base.hpp bfs.hpp
