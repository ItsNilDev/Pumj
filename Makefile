
all: main.cpp
	g++ -c main.cpp
	g++ -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system main.o
	./sfml-app
