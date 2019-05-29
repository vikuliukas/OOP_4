#CXX = clang++
CXXFLAGS=  -Wall -g
#CC = clang

all: main.o funkcijos.o operatoriai.o irasymas.o skaitymas.o
	g++  main.o funkcijos.o operatoriai.o irasymas.o skaitymas.o -o main

main.o: main.cpp

funkcijos.o: funkcijos.cpp

operatoriai.o: operatoriai.cpp

irasymas.o: irasymas.cpp

skaitymas.o: skaitymas.cpp

test:	all
	./main

clean:
	rm -f *.o main vargšiukai.txt šaunuoliai.txt