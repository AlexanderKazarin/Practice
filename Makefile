all: translator

translator: main.o Wordbook.o
	g++ -o translator main.o Wordbook.o -std=c++11

main.o: main.c++
	g++ -c main.c++ -std=c++11

Wordbook.o: Wordbook.c++ Wordbook.h
	g++ -c Wordbook.c++ -std=c++11

clean:
	rm -rf translator *.o