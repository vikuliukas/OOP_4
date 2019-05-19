#CXX = clang++
CXXFLAGS=  -Wall -g
#CC = clang

all: main.o vector.o
	g++  main.o vector.o -o main

main.o: main.cpp

vector.o: vector.cpp

test:	all
	./main

clean:
	rm -f *.o main