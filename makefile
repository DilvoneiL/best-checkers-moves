all:dama.o
	gcc dama.o main.c -o main

tp1.o:dama.h
	gcc -c dama.c

clean:
	rm -rf *.o main