all: compile link open

compile:
	g++ -Isrc/include -c main.cpp animation.cpp pacman.cpp move.cpp map.cpp food.cpp menu.cpp ghost.cpp

link:
	g++ main.o animation.o pacman.o move.o map.o food.o menu.o ghost.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

open:
	./main

g++ -Isrc/include -c main.cpp animation.cpp pacman.cpp move.cpp map.cpp food.cpp menu.cpp ghost.cpp; g++ main.o animation.o pacman.o move.o map.o food.o menu.o ghost.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system; ./main