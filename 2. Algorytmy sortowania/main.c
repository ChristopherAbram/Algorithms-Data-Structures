#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "sort.h"

#define MAX_HUGE_ARRAY_SIZE  	131072000
#define MAX_SMALL_ARRAY_SIZE  	256000
#define MAX_LEN	    		512

#define HUGE_TEST 	1
#define SMALL_TEST 	0

void _copyArray(intptr_t*, intptr_t*, size_t);
void _putString(const char*);
void _generateRandomIntArray(intptr_t*, size_t, int, int);
void _arrayReverse( intptr_t*, size_t );
void createFile( const char*, intptr_t*, size_t);
void readFile(const char*, intptr_t*, size_t);
int fileExists(const char*);
void clearBuffer(void);
char *_toPolish(char*);
void throwException(const char*);
void errnoException(const char*);
void closeAllStream(void);

char msg[10][MAX_LEN] = {
	"Sortowanie przez wstawianie",
	"Sortowanie przez selekcje",
	"Sortowanie babelkowe",
	"Sortowanie szybkie",
	"Sortowanie Shell\'a",
	"Sortowanie przez kopcowanie",
	"liczba elementow w sortowanym zbiorze",
	"czas sortowania zbioru [s]",
};

char testMsg[3][MAX_LEN] = {
	"Test 1: Dane wygenerowane losowo:",
	"Test 2: Dane posortowane w kolejnosci malejacej:",
	"Test 3: Dane posortowane w kolejnosci rosnacej:",
};

char error[10][MAX_LEN] = {
	"Wyst±pi³ b³±d",
	"Wyst±pi³ b³±d podczas zamykania plików",
	"B³±d czytania pliku",
	"Podano zbyt du¿y rozmiar danych",
	"Wyst±pi³ b³±d podczas czytania pliku"
};

int main(){
	/* zmienne techniczne programu: */
	size_t size;
	size_t testSize[6][3][3] = {
		// insertion sort:
		{
			/* min_size, max_size, test_type */
			{ 1000, 256000, SMALL_TEST }, // test 1
			{ 1000, 256000, SMALL_TEST },     // test 2
			{ 256000, 131072000, HUGE_TEST },     // test 3
		},
		// selection sort:
		{
			{ 1000, 256000, SMALL_TEST },	// test 1
			{ 1000, 256000, SMALL_TEST },	// test 2
			{ 1000, 256000, SMALL_TEST },	// test 3
		},
		// bubble sort:
		{
			{ 1000, 256000, SMALL_TEST },	  // test 1
			{ 1000, 256000, SMALL_TEST },	  // test 2
			{ 256000, 131072000, HUGE_TEST }, // test 3
		},
		// quick sort:
		{
			{ 256000, 131072000, HUGE_TEST }, // test 1
			{ 256000, 131072000, HUGE_TEST }, // test 2
			{ 256000, 131072000, HUGE_TEST }, // test 3
		},
		// shell sort:
		{
			{ 256000, 131072000, HUGE_TEST }, // test 1
			{ 256000, 131072000, HUGE_TEST }, // test 2
			{ 256000, 131072000, HUGE_TEST }, // test 3
		},
		// heap sort:
		{
			{ 256000, 131072000, HUGE_TEST }, // test 1
			{ 256000, 131072000, HUGE_TEST }, // test 2
			{ 256000, 131072000, HUGE_TEST }, // test 3
		},
	};
	size_t i; // zmienna steruj±ca pêtli inkrementuj±cej rozmiar danych
	size_t test; // zmienna steruj±ca pêtli wykonywanego testu
	size_t currentFunction; // zmienna wskazuj±ca indeks testowanej funkcji
	int p;

	/* tablice numeryczne z danymi testowymi: */
	intptr_t *arrayHuge = NULL;
	intptr_t *arraySmall = NULL;
	intptr_t *copyOfArray = NULL;

	/* zmienne czasowe: */
	clock_t before, after;
	double time = 0.; // czas sortowania zbioru

	/* pliki: */
	const char setASC_HugeFile[] = "HugeData.txt";
	const char setASC_SmallFile[] = "SmallData.txt";
	
	/* testowane funkcje: */
	void (*function[6])(intptr_t*, size_t, int) = {
		insertionSort,
		selectionSort,
		bubbleSort,
		quickSort,
		shellSort,
		heapSort,
	};

	// lokowanie dynamiczne potrzebnej pamiêci {
	
	arrayHuge = (int*)malloc(MAX_HUGE_ARRAY_SIZE * sizeof(int));
	arraySmall = (int*)malloc(MAX_SMALL_ARRAY_SIZE * sizeof(int));
	copyOfArray = (int*)malloc(MAX_HUGE_ARRAY_SIZE * sizeof(int));

	// } generowanie losowych danych {
	
	printf("\r Prosze czekac, trwa generowanie liczb losowych...");fflush(stdout);
	_generateRandomIntArray(arrayHuge, MAX_HUGE_ARRAY_SIZE, -100, 100);
	_generateRandomIntArray(arraySmall, MAX_SMALL_ARRAY_SIZE, -100, 100);

	// }  tworzymy pliki z danymi posortowanymi rosn±co {

	if (!fileExists(setASC_HugeFile)){ // je¶li plik istnieje, to nie tworzymy nowego
		printf("\r Prosze czekac, trwa tworzenie pliku: %s...       ", setASC_HugeFile);fflush(stdout);
		_copyArray(arrayHuge, copyOfArray, MAX_HUGE_ARRAY_SIZE);
		shellSort(copyOfArray, MAX_HUGE_ARRAY_SIZE, SORTASC);
		createFile(setASC_HugeFile, copyOfArray, MAX_HUGE_ARRAY_SIZE);
		printf("\r Poprawnie utworzono plik : %s                    ", setASC_HugeFile);fflush(stdout);
	}

	if (!fileExists(setASC_SmallFile)){ // je¶li plik istnieje, to nie tworzymy nowego
		printf("\r Prosze czekac, trwa tworzenie pliku: %s...       ", setASC_SmallFile);fflush(stdout);
		_copyArray(arraySmall, copyOfArray, MAX_SMALL_ARRAY_SIZE);
		shellSort(copyOfArray, MAX_SMALL_ARRAY_SIZE, SORTASC);
		createFile(setASC_SmallFile, copyOfArray, MAX_SMALL_ARRAY_SIZE);
		printf("\r Poprawnie utworzono plik : %s                    ", setASC_SmallFile);fflush(stdout);
	}

	// } ekran powitalny i menu {

		printf("\r------------------------------------------------------\n");fflush(stdout);
		printf("             TESTY ALGORYTMOW SORTOWANIA\n" );
		printf("------------------------------------------------------\n");
		printf(" Sortowanie przez wstawianie:                       1\n");
		printf(" Sortowanie przez selekcje:                         2\n");
		printf(" Sortowanie babelkowe:                              3\n");
		printf(" Sortowanie szybkie:                                4\n");
		printf(" Sortowanie Shell\'a:                                5\n");
		printf(" Sortowanie przez kopcowanie:                       6\n");
		printf("------------------------------------------------------\n");
		printf(" Wyjscie:                                           7\n");
		printf("---------------------------------- Krzysztof Abram ---\n\n\n");

		printf("--- Legenda ------------------------------------------\n\n");
		printf("- n - %s\n", _toPolish(msg[6]) );
		printf("- time - %s\n\n", _toPolish(msg[7]));
		printf("--- Opis ---------------------------------------------\n\n");
		printf(" Wybierz numer funkcji z menu i obserwuj rezultaty \n testu wykonywanego calkowicie automatycznie. Dla \n kazdej funkcji zostana wykonane trzy testy:\n - Test 1 - dla danych wygenerowanych losowo,\n - Test 2 - dla danych posortowanych malejaco,\n - Test 3 - dla danych posortowanych rosnaco.\n Dobrano takie rozmiary danych dla kazdej funkcji \n oraz poszczegolnego testu, ze sortowanie odbedzie\n sie w rozsadnym czasie.\n\n");
		printf("------------------------------------------------------\n");

	// }

		do{
			// wybór funkcji {

			printf("\n\n");
			printf(" Wybieram: _\b");fflush(stdout);

			p = scanf("%d", &currentFunction);
			clearBuffer();
			if (!p || currentFunction > 7 || currentFunction < 1){
				do{
					printf(" Podano nieodpowiednia cyfre. Wybieram: _\b");
					p = scanf("%d", &currentFunction);
					clearBuffer();
				} while (!p || currentFunction > 7 || currentFunction < 1);
			}
			
			// } koniec programu {

			if (currentFunction == 7){
				if(arrayHuge) free(arrayHuge);
				if (arraySmall) free(arraySmall);
				if(copyOfArray) free(copyOfArray);
				exit(0);
			}
			
			// } przetwarzanie numeru funkcji na indeks {
			currentFunction--;
			printf("\n\n------------------------------------------------------\n");
			printf(" WYNIKI: %s.\n", _toPolish(msg[currentFunction]));fflush(stdout);

			// } obliczenia {

			for (test = 0; test < 3; test++){
				printf( "\n %s\n\n", _toPolish(testMsg[test]) );
				printf(" |-------------------|-----------------------|\n");
				printf(" |                 n |              time [s] |\n");
				printf(" |-------------------|-----------------------|\n");
				fflush(stdout);
				for (size = testSize[currentFunction][test][0]; size <= testSize[currentFunction][test][1]; size *= 2){
					switch (test){
						case 0: // test 1: dane losowe
						{
							// pobieramy kopiê danych wygenerowanych losowo {

							printf("\r           ...Pobieranie danych...");fflush(stdout);
							if (testSize[currentFunction][test][2] == HUGE_TEST)
								_copyArray(arrayHuge, copyOfArray, size);
							else if (testSize[currentFunction][test][2] == SMALL_TEST)
								_copyArray(arraySmall, copyOfArray, size);

							// } obliczamy czas sortowania dla danych losowych {

							printf("\r              ...Sortowanie...    ");fflush(stdout);
							before = clock();
							function[currentFunction](copyOfArray, size, SORTASC);
							after = clock();
							time = (double)(after - before) / CLOCKS_PER_SEC;

							// }
						}; break;
						case 1: // test 2: dane posortowane malej±co
						{
							// pobieramy dane z pliku posortowane malej±co {

							printf("\r           ...Pobieranie danych...");fflush(stdout);
							if (testSize[currentFunction][test][2] == HUGE_TEST)
								readFile(setASC_HugeFile, copyOfArray, size);
							else if (testSize[currentFunction][test][2] == SMALL_TEST)
								readFile(setASC_SmallFile, copyOfArray, size);

							_arrayReverse(copyOfArray, size); // odwracamy kolejno¶æ, bo dane posortowane s± rosn±co

							// } obliczamy czas dla danych z pliku (posortowanych malej±co) {

							printf("\r              ...Sortowanie...    ");fflush(stdout);
							before = clock();
							function[currentFunction](copyOfArray, size, SORTASC);
							after = clock();
							time = (double)(after - before) / CLOCKS_PER_SEC;

							// }
						}; break;
						case 2: // test 3: dane posortowane rosn±co
						{
							// pobieramy dane z pliku posortowane rosn±co {

							printf("\r           ...Pobieranie danych...");fflush(stdout);
							if (testSize[currentFunction][test][2] == HUGE_TEST)
								readFile(setASC_HugeFile, copyOfArray, size);
							else if (testSize[currentFunction][test][2] == SMALL_TEST)
								readFile(setASC_SmallFile, copyOfArray, size);

							// } obliczamy czas dla danych z pliku (posortowanych rosn±co) {

							printf("\r              ...Sortowanie...    ");fflush(stdout);
							before = clock();
							function[currentFunction](copyOfArray, size, SORTASC);
							after = clock();
							time = (double)(after - before) / CLOCKS_PER_SEC;

							// }
						}; break;
					}
					printf("\r | %17ld |             % 9.6lf |\n", size, time);fflush(stdout);
				}
				printf(" |-------------------|-----------------------|\n");
			}

			// }
		} while ( currentFunction < 7 );
}// end main

void _putString(const char *string ){
	unsigned int i;
	while(*(string + i) != '\0') putchar(*(string + i));
}// end _putString

/* _copyArray - kopuje tablicê typu int array do tablicy copy
* array - tablica oryginalna,
* copy - tablica kopia,
* size - rozmiar tablic
*/
void _copyArray(intptr_t *array, intptr_t *copy, size_t size){
	size_t i;
	for (i = 0; i < size; i++)
		copy[i] = array[i];
}// end _copyArray

/* _generateRandomIntArray - wype³nia tablicê array warto¶ciami losowymi z przedzia³u <left, right>
* array - tablica oryginalna,
* size - rozmiar tablic,
* left - pocz±tek przedzia³u losowania,
* right - koniec przedzia³u losowania,
*/
void _generateRandomIntArray(intptr_t *array, size_t size, int left, int right){
	size_t i;
	int tmp;
	if (right < left){ // gdyby ¼le podano przedzia³
		tmp = left;
		left = right;
		right = tmp;
	}
	srand( time(NULL) );
	for (i = 0; i < size; i++)
		array[i] = right - rand() % (right - left + 1); // zakres <left, right>
}// end _generateRandomIntArray

/* _arrayReverse - odwraca kolejno¶æ elementów w tablicy array
* array - tablica,
* size - wielko¶æ tablicy
*/
void _arrayReverse(intptr_t *array, size_t size){
	size_t i;
	int tmp;
	for (i = 0; i < (size / 2); i++){
		tmp = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = tmp;
	}
}// end _arrayReverse

/* fileExists - sprawdza czy plik o podanej nazwie istnieje
* filename - nazwa pliku
*/
int fileExists( const char *filename ){
	if (access(filename, 0) != -1)
		return 1;
	return 0;
}// end fileExists

/* createFile - tworzy plik tekstowy i wype³nia go danymi. Format [size N1 N2 N3 N4 N5 ... Nsize]
* filename - nazwa pliku
* data - dane do zapisu (tablica)
* size - rozmiar danych
*/
void createFile(const char *filename, intptr_t *data, size_t size){
	FILE *file = NULL;
	size_t i;

	// tworzenie pliku :
	file = fopen(filename, "wt");
	if (!file) errnoException(_toPolish(error[0]));

	// zapisywanie danych :
	fprintf(file, "%ld ", size);
	for (i = 0; i < size; i++){
		fprintf(file, "%d ", data[i]);
	}
	if (file) fclose(file);
}// end createFile

/* readFile - czyta plik tekstowy i wype³nia danymi tablicê data o d³ugo¶ci size. Format [size N1 N2 N3 N4 N5 ... Nsize]
* filename - nazwa pliku
* data - tablica przechowujaca dane
* size - rozmiar danych (do odczytu)
*/
void readFile(const char *filename, intptr_t *data, size_t size){
	FILE *file = NULL;
	size_t i;
	int p;
	size_t sizeInFile = 0;

	// otwieranie istniejacego pliku :
	file = fopen(filename, "rt");
	if (!file) errnoException(_toPolish(error[0]));

	// czytanie warto¶ci z pliku {
		if (!fscanf(file, "%d", &sizeInFile)) errnoException( _toPolish(error[2]) );
		if (sizeInFile < size) throwException( _toPolish( error[3] ) );

		p = 0;
		for (i = 0; i < size; i++){
			p = fscanf(file, "%d", &data[i]);
			if (!p) break;
		}

		if (p);// printf("Poprawnie odczytano dane.\n");
		else throwException( _toPolish( error[4] ) );
	// }

	if (file) fclose(file);
}// end readFile

void clearBuffer(void){
	while (getchar() != '\n');
}// end clearBuffer

char *_toPolish(char *string){
	char c; int i, strLength = 0;
	char polishChars[18] = {
		'±', 'æ', 'ê', '³', 'ñ', 'ó', '¶', '¼', '¿',
		'¡', 'Æ', 'Ê', '£', 'Ñ', 'Ó', '¦', '¬', '¯',
	};
	int ASCIIequ[18] = {
		165, 134, 169, 136, 228, 162, 152, 171, 190,
		164, 143, 168, 157, 227, 224, 151, 141, 189,
	}; // Latin II
	while ((c = *string) != '\0'){
		for (i = 0; i < 18; i++)
			if (c == polishChars[i]){
				*string = (char)ASCIIequ[i];
				break;
			}
		string++;
		strLength++;
	}
	return (string - strLength);
}// end _toPolish

void closeAllStream(void){
	/*if (_fcloseall() == EOF){ // zamyka wszystkie strumienie z wyj±tkiem stdin, stdout, stderr
		printf("%s", _strerror( _toPolish(error[1]) ));
		clearBuffer();
		exit(1);
	}*/
}// end closeAllStream

void errnoException(const char *exceptionString){
	printf("%s: %s\n", exceptionString, strerror(errno));
	closeAllStream();
	clearBuffer();
	getchar();
	exit(1);
}// end myException

void throwException(const char *exceptionString){
	printf("%s\n", exceptionString);
	closeAllStream();
	clearBuffer();
	getchar();
	exit(1);
}// end myException
