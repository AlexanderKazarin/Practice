all: translator quiz

translator: main.o Dictionary.o
	g++ -o translator main.o Dictionary.o -std=c++14

quiz: quiz.o
	g++ -o quiz quiz.o -std=c++14

quiz.o: quiz.cpp
	g++ -c quiz.cpp -std=c++14

main.o: main.cpp
	g++ -c main.cpp -std=c++14

Dictionary.o: Dictionary.cpp Dictionary.h
	g++ -c Dictionary.cpp -std=c++14

clean:
	rm -rf translator quiz *.o