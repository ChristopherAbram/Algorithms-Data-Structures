/***
* sort.c - implementacja funkcji biblioteki sort.h.
*
* Copyright (c) Krzysztof Abram
*
****/

#ifndef __SORT_C
#define __SORT_C

#include "sort.h"

/* insertionSort - metoda sortowania przez wstawianie
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void insertionSort(intptr_t *array, size_t size, int flag){
	int x; // wybrany ze zbioru element
	size_t i, j; // zmienne sterujace pêtli

	if (flag == SORTASC){ // sortowanie w kolejnoœci rosn¹cej
		for (j = size; j >= 1; j--){
			x = array[j-1];
			i = j;
			while (i < size && x > array[i]){
				array[i - 1] = array[i];
				i++;
			}
			array[i - 1] = x;
		}
	}
	else if (flag == SORTDESC){ // sortowanie w kolejnoœci malej¹cej
		for (j = size; j >= 1; j--){
			x = array[j - 1];
			i = j;
			while (i < size && x < array[i]){
				array[i - 1] = array[i];
				i++;
			}
			array[i - 1] = x;
		}
	}
}// end insertionSort

/* selectionSort - metoda sortowania przez selekcjê(wybór)
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void selectionSort(intptr_t *array, size_t size, int flag){
	size_t p; // pozycja elementu o wartoœci najmniejszej lub najwiêkszej w zbiorze
	size_t i, j; // zmienne steruj¹ce pêtl¹
	int tmp; // zmienna pomocnicza

	if ( flag == SORTASC ){ // sortowanie w kolejnoœci rosn¹cej
		for (j = 0; j < size; j++){
			p = j;
			for (i = j + 1; i < size; i++)
				if (array[i] < array[p])
					p = i;
			tmp = array[j];
			array[j] = array[p];
			array[p] = tmp;
		}
	}
	else if ( flag == SORTDESC ){ // sortowanie w kolejnoœci malej¹cej
		for (j = 0; j < size; j++){
			p = j;
			for (i = j + 1; i < size; i++)
				if (array[i] > array[p])
					p = i;
			tmp = array[j];
			array[j] = array[p];
			array[p] = tmp;
		}
	}
}// end selectionSort

/* bubbleSort - metoda sortowania przez b¹belkowanie
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void bubbleSort(intptr_t *array, size_t size, int flag){
	size_t pmin, pmax; // pozycje elementów o wartoœci najmniejszej, najwiêkszej
	size_t p; // numer pozycji zamiany elementów
	size_t i; // zmienne steruj¹ce pêtli
	int tmp; // zmienna pomocnicza

	if (flag == SORTASC){ // sortowanie w kolejnoœci rosn¹cej
		pmin = 0; pmax = size - 1;
		do{
			p = 0;
			for (i = pmin; i < pmax; i++)
				if (array[i] > array[i + 1]){
					tmp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = tmp;
					if (p < 1) pmin = i;
					p = i + 1;
				}
			if (pmin) pmin--;
			pmax = p - 1;
		} while ( p >= 1 );
	}
	else if (flag == SORTDESC){ // sortowanie w kolejnoœci malej¹cej
		pmin = 0; pmax = size - 1;
		do{
			p = 0;
			for (i = pmin; i < pmax; i++)
				if (array[i] < array[i + 1]){
					tmp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = tmp;
					if (p < 1) pmin = i;
					p = i + 1;
				}
			if (pmin) pmin--;
			pmax = p - 1;
		} while (p >= 1);
	}
}// end bubbleSort

/* _quickSortASC - algorytm sortowania szybkiego w kierunku rosn¹cym
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* left - indeks pierwszego elementu w zbiorze,
* right - indeks ostatniego elementu w zbiorze
*/
void static _quickSortASC(intptr_t *array, long int left, long int right){
	long int i, j; // indeksy
	long int pivot; // piwot - element podzia³owy
	int tmp, x;

	i = left;
	j = right;
	pivot = (long int)(left + right) / 2;
	x = array[pivot];
	do {
		while (array[i] < x) i++;
		while (array[j] > x) j--;

		if (i <= j){
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) _quickSortASC(array, left, j);
	if (right > i) _quickSortASC(array, i, right);
	return;
}// end _quickSortASC

/* _quickSortDESC - algorytm sortowania szybkiego w kierunku malej¹cym
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* left - indeks pierwszego elementu w zbiorze,
* right - indeks ostatniego elementu w zbiorze
*/
void static _quickSortDESC(intptr_t *array, long int left, long int right){
	long int i, j; // indeksy
	long int pivot; // piwot - element podzia³owy
	int tmp, x;

	i = left;
	j = right;
	pivot = (long int)(left + right) / 2;
	x = array[pivot];
	do {
		while (array[i] > x) i++;
		while (array[j] < x) j--;

		if (i <= j){
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) _quickSortDESC(array, left, j);
	if (right > i) _quickSortDESC(array, i, right);
	return;
}// end _quickSortDESC

/* quickSort - algorytm sortowania szybkiego
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void quickSort(intptr_t *array, size_t size, int flag){
	if (flag == SORTASC)
		_quickSortASC( array, 0, size - 1 );
	else if (flag == SORTDESC)
		_quickSortDESC( array, 0, size - 1 );
}// end quickSort

/* shellSort - algorytm sortowania Shell'a
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void shellSort(intptr_t *array, size_t size, int flag){
	size_t i; // indeks elementu listy uporz¹dkowanej,
	size_t j; // zmienna steruj¹ca pêtli,
	size_t h; // odstêp pomiêdzy kolejnymi elementami podzbiorów,
	int x; // zawiera wybrany ze zbioru element

	for (h = 1; h < size; h = 3 * h + 1);
	h /= 9;
	if (!h) h++; // istotne dla ma³ych rozmiarów zbioru array

	if (flag == SORTASC){
		while (h){
			for (j = (size - h); j >= 1; j--){
				x = array[j - 1];
				i = j - 1 + h;
				while ((i < size) && (x > array[i])){
					array[i - h] = array[i];
					i += h;
				}
				array[i - h] = x;
			}
			h /= 3;
		}
	}
	else if (flag == SORTDESC){
		while (h){
			for (j = (size - h); j >= 1; j--){
				x = array[j - 1];
				i = j - 1 + h;
				while ((i < size) && (x < array[i])){
					array[i - h] = array[i];
					i += h;
				}
				array[i - h] = x;
			}
			h /= 3;
		}
	}
}// end shellSort

/* _buildHeap - algorytm budowania kopca
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek budowania (rosn¹co/malej¹co),
*/
void static _buildHeap(intptr_t *array, size_t size, int flag){
	size_t i; //  zmienna licznikowa pêtli umieszczaj¹cej kolejne elementy zbioru w kopcu
	size_t j, k; // indeksy elementów le¿¹cych na œcie¿ce od wstawianego elementu do korzenia
	int x; // zmienna pomocnicza przechowuj¹ca tymczasowo element wstawiany do kopca

	if (flag == SORTASC){ // budowanie kopca rosn¹co
		for (i = 2; i < size; i++){
			j = i;
			k = j / 2;
			x = array[i];
			while ((k > 0) && (array[k] < x)){
				array[j] = array[k];
				j = k;
				k = j / 2;
			}
			array[j] = x;
		}
	}
	else if (flag == SORTDESC){ // budowanie kopca malej¹co
		for (i = 2; i < size; i++){
			j = i;
			k = j / 2;
			x = array[i];
			while ((k > 0) && (array[k] > x)){
				array[j] = array[k];
				j = k;
				k = j / 2;
			}
			array[j] = x;
		}
	}
}// end _buildHeap

/* _destroyHeap - algorytm rozbierania kopca (w miejscu)
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek rozbierania (rosn¹co/malej¹co),
*/
void static _destroyHeap(intptr_t *array, size_t size){
	size_t i; // zmienna licznikowa pêtli pobieraj¹cej kolejne elementy z kopca
	size_t j, k; // indeksy elementów le¿¹cych na œcie¿ce w dó³ od korzenia
	size_t m; // indeks wiêkszego z dwóch elementów potomnych
	int tmp; // zmienna tymczasowa

	for (i = size - 1; i > 1; i--){
		tmp = array[1];
		array[1] = array[i];
		array[i] = tmp;
		j = 1;
		k = 2;
		while (k < i){
			if ((k + 1 < i) && (array[k + 1] > array[k]))
				m = k + 1;
			else
				m = k;
			if (array[m] <= array[j]) break;
			tmp = array[j];
			array[j] = array[m];
			array[m] = tmp;
			j = m;
			k = 2 * j;
		}
	}
}// end _destroyHeap

/* heapSort - algorytm sortowania przez kopcowanie
* *array - wskaŸnik wskazuj¹cy na pocz¹tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void heapSort(intptr_t *array, size_t size, int flag){
	_buildHeap(array, size, flag); // budujemy kopiec
	_destroyHeap(array, size); // rozbieramy kopiec
}// end heapSort

#endif /* __SORT_C */
