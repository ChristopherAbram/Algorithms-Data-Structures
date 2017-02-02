/***
* RedBlackTree.h - definicje oraz deklaracje dla biblioteki obs�uj�cej drzewo czerwono-czarne.
*
*       Copyright (c) Krzysztof Abram
*
* Cel:
*       Ten plik definiuje warto�ci, makra oraz funkcje
*		u�ywane w celu wykonywania operacji na strukturze drzewa czerwono-czarnego.
*
*       [Public]
*
****/

#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#include <stdio.h>
#include <string.h>

#define RED		'R'
#define BLACK	'B'

#define MAX_PRINT_LEN 512

struct _RBTNode {
	struct _RBTNode *up;
	struct _RBTNode *left;
	struct _RBTNode *right;
	int key;
	char color;
};
typedef struct _RBTNode RBTNode;

extern RBTNode *root;
extern RBTNode *sentinelNode; // li�� wartownik
extern char *cr, *cl, *cp;

/* initializeTree - inicjuje drzewo
* tree - wska�nik do drzewa
@ return: void
*/
void initializeTree( );

/* initializeNode - inicjuje w�ze�
* node - wska�nik do w�z�a
@ return: void
*/
void initializeNode(RBTNode *node);

/* newNode - tworzy miejsce w pami�ci dla nowego w�z�a
@ return: wska�nik do pami�ci alokowanej dynamicznie 
*/
RBTNode *newNode( void );

/* unsetNode - dealokuje miejsce w pami�ci dla wskazanego w�z�a
@ return: void
*/
void unsetNode(RBTNode *node);

/* findNode - Wyszukuje w�ze� o kluczu k
* k - klucz,
@ return: wska�nik do w�z�� zawieraj�cego klucz o warto�ci k,
*/
RBTNode *findRBT(int k);

/* minRBT - szuka najmniejszego w�z�a
* node - korze�,
@ return: wska�nik do najmniejszego w�z�a
*/
RBTNode *minRBT(RBTNode *node);

/* succRBT - zwaraca nast�pnik node
* node - w�ze�
@ return: wska�nik do w�z�a, kt�ry jest nast�pnikiem node
*/
RBTNode *succRBT(RBTNode *node);

/* rot_L - wykonuje rotacj� drzewa w lewo wzgl�dem w�z�a node
* node - w�ze�
@ return: void
*/
void rot_L(RBTNode *node);

/* rot_R - wykonuje rotacj� drzewa w prawo wzgl�dem w�z�a node
* node - w�ze�
@ return: void
*/
void rot_R(RBTNode *node);

/* insertRBT - wstawia nowy w�ze� o kluczu k do drzewa
* k - klucz,
@ return: void
*/
void insertRBT(int k);

/* removeRBT - usuwa w�ze� node z drzewa
* node - usuwany w�ze�,
@ return: void
*/
void removeRBT(RBTNode *node);

/* DFSRelease - usuwa drzewo rekurencyjnie,
* node - korze� drzewa,
@ return: void
*/
void DFSRelease(RBTNode *node);

/* printRBT - wy�wietla drzewo w konsoli
* node - korze� drzewa,
@ return: void
*/
void printRBT(RBTNode *node);

#endif /* __RED_BLACK_TREE__ */