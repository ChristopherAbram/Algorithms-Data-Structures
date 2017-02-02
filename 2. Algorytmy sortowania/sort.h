/***
* sort.h - definicje oraz deklaracje dla biblioteki sortujπcej.
*
*       Copyright (c) Krzysztof Abram
*
* Cel:
*       Ten plik definiuje wartoúci, makra oraz funkcje 
*		uøywane w celu wykonywania sortowaÒ zbiorÛw numerycznych.
*		
*       [Public]
*
****/

#ifndef __SORT__
#define __SORT__

#include <stdio.h>
#include <stdint.h>

#define SORTDESC 0x01 // sortowanie malejaco
#define SORTASC  0x02 // sortowanie rosnπco

/* insertionSort - metoda sortowania przez wstawianie
* *array - wskaünik wskazujπcy na poczπtek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void insertionSort( intptr_t *array, size_t size, int flag );

/* selectionSort - metoda sortowania przez selekcjÍ(wybÛr)
* *array - wskaünik wskazujπcy na poczπtek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void selectionSort(intptr_t *array, size_t size, int flag);

/* bubbleSort - metoda sortowania przez bπbelkowanie
* *array - wskaünik wskazujπcy na poczπtek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void bubbleSort(intptr_t *array, size_t size, int flag);

/* quickSort - algorytm sortowania szybkiego
* *array - wskaünik wskazujπcy na poczπtek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void quickSort(intptr_t *array, size_t size, int flag);

/* shellSort - algorytm sortowania Shell'a
* *array - wskaünik wskazujπcy na poczπtek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void shellSort(intptr_t *array, size_t size, int flag);

/* heapSort - algorytm sortowania przez kopcowanie
* *array - wskaünik wskazujπcy na poczπtek tablicy,
* size - rozmiar tablicy,
* flag - kierunek sortowania,
*/
void heapSort(intptr_t *array, size_t size, int flag);

#endif /* __SORT__ */
