#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "RedBlackTree.h"

#define MAX_SIZE 25

void swap(int*,int*);
int randomNumber( int, int );

int main( void ){
	int arrayKey[MAX_SIZE];
	size_t i, first, second;
	int tmp;

	srand(time(NULL));

	initializeTree(); // inicjujemy drzewo

	printf(" --------------------------------------------------------------\n\n");
	printf("                     Drzewo czerwono-czarne                    \n\n");
	printf(" --------------------------------------------------------------\n");
	printf("                                                Krzysztof Abram\n\n");

	printf(" Losujemy %d liczb, ktore sa kluczami wezlow w drzewie,\n nastepnie na podstawie kluczy budujemy drzewo czerwono-czarne.\n R - wezel czerwony (red)\n B - wezel czarny (black)\n\n", MAX_SIZE);

	// wyype³niamy tablicê losowymi kluczami: [0, 1000]
	for (i = 0; i < MAX_SIZE; i++)
		arrayKey[i] = randomNumber(0, 1000);

	// tworzymy drzewo czerwono czarne (na podstawie kluczy):
	for (i = 0; i < MAX_SIZE; i++)
		insertRBT(arrayKey[i]);

	// wyœwietlamy drzewo:
	printf("\n Utworzone drzewo:\n\n");
	printRBT(root);

	// tasujemy tablicê kluczy:
	for (i = 0; i < 3 * MAX_SIZE; i++){
		first = rand() % MAX_SIZE;
		second = rand() % MAX_SIZE;
		swap(&arrayKey[first], &arrayKey[second]);
	}

	// usuwamy co najwy¿ej po³owê tablicy:
	for (i = 0; i < MAX_SIZE >> 1; i++)
		removeRBT(findRBT(arrayKey[i]));

	// wyœwietlamy drzewo:
	printf("\n\n Usuwamy polowe drzewa: (losowe elementy)\n\n");
	printRBT(root);

	// tasujemy tablicê kluczy:
	for (i = 0; i < 3 * MAX_SIZE; i++){
		first = rand() % MAX_SIZE;
		second = rand() % MAX_SIZE;
		swap(&arrayKey[first], &arrayKey[second]);
	}

	// usuwamy co najwy¿ej po³owê tablicy:
	for (i = 0; i < MAX_SIZE >> 2; i++)
		removeRBT(findRBT(arrayKey[i]));

	// wyœwietlamy drzewo:
	printf("\n\n Jeszcze raz usuwamy polowe drzewa:\n\n");
	printRBT(root);

	// usuwamy drzewo
	DFSRelease(root);

	getchar();
}// end main

void swap( int *var_1, int *var_2 ){
	int tmp;
	tmp = *var_1;
	*var_1 = *var_2;
	*var_2 = tmp;
	return;
}// end swap

int randomNumber(int a, int b){
	return (rand() % (b - a + 1) + a);
}// end randomNumber