#!make -f

CXX=clang++-9 
CXXFLAGS=-std=c++2a

HEADERS=range.hpp accumulate.hpp filterfalse.hpp compress.hpp
OBJECTS=

run: demo
	./$^

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test
