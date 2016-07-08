all: translator

translator: main.o Dictionary.o
	g++ -o translator main.o Dictionary.o -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11

Dictionary.o: Dictionary.cpp Dictionary.h
	g++ -c Dictionary.cpp -std=c++11

clean:
	rm -rf translator *.o