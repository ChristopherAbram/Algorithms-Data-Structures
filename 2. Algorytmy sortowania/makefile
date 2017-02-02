all: sort
sort: main.o sort.o
	gcc -o sort main.o sort.o
main.o: main.c sort.h
	gcc -c main.c
sort.o: sort.c sort.h
	gcc -c sort.c
clean:
	rm *.o
