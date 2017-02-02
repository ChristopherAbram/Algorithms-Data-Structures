/***
* sort.h - definicje oraz deklaracje dla biblioteki sortuj�cej.
*
*       Copyright (c) Krzysztof Abram
*
* Cel:
*       Ten plik definiuje warto�ci, makra oraz funkcje 
*		u�ywane w celu wykonywania sortowa� zbior�w numerycznych.
*		
*       [Public]
*
****/

#ifndef __SORT__
#define __SORT__

#include <stdio.h>
#include <stdint.h>

#define SORTDESC 0x01 // sortowanie malejaco
#define SORTASC  0x02 // sortowanie rosn�co

/* insertionSort - metoda sortowania przez wstawianie
* *array - wska�nik wskazuj�cy na pocz�tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void insertionSort( intptr_t *array, size_t size, int flag );

/* selectionSort - metoda sortowania przez selekcj�(wyb�r)
* *array - wska�nik wskazuj�cy na pocz�tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void selectionSort(intptr_t *array, size_t size, int flag);

/* bubbleSort - metoda sortowania przez b�belkowanie
* *array - wska�nik wskazuj�cy na pocz�tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void bubbleSort(intptr_t *array, size_t size, int flag);

/* quickSort - algorytm sortowania szybkiego
* *array - wska�nik wskazuj�cy na pocz�tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void quickSort(intptr_t *array, size_t size, int flag);

/* shellSort - algorytm sortowania Shell'a
* *array - wska�nik wskazuj�cy na pocz�tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void shellSort(intptr_t *array, size_t size, int flag);

/* heapSort - algorytm sortowania przez kopcowanie
* *array - wska�nik wskazuj�cy na pocz�tek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void heapSort(intptr_t *array, size_t size, int flag);

#endif /* __SORT__ */
