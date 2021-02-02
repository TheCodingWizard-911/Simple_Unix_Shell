all: main

main: main.o shell.o builtin.o
	gcc main.o shell.o builtin.o -o main

main.o: main.c
	gcc -c main.c

shell.o: shell.c
	gcc -c shell.c

builtin.o: builtin.c
	gcc -c builtin.c

clean:
	rm -rf *.o  *.out main