exe: programa
	./programa

programa: main.o
		gcc -Wall -o programa main.o -lrt

main.o: main.c funciones.h
		gcc -Wall -c main.c