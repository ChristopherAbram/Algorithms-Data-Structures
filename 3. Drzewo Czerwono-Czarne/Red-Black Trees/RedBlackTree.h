/***
* RedBlackTree.h - definicje oraz deklaracje dla biblioteki obs³uj¹cej drzewo czerwono-czarne.
*
*       Copyright (c) Krzysztof Abram
*
* Cel:
*       Ten plik definiuje wartoœci, makra oraz funkcje
*		u¿ywane w celu wykonywania operacji na strukturze drzewa czerwono-czarnego.
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
extern RBTNode *sentinelNode; // liœæ wartownik
extern char *cr, *cl, *cp;

/* initializeTree - inicjuje drzewo
* tree - wskaŸnik do drzewa
@ return: void
*/
void initializeTree( );

/* initializeNode - inicjuje wêze³
* node - wskaŸnik do wêz³a
@ return: void
*/
void initializeNode(RBTNode *node);

/* newNode - tworzy miejsce w pamiêci dla nowego wêz³a
@ return: wskaŸnik do pamiêci alokowanej dynamicznie 
*/
RBTNode *newNode( void );

/* unsetNode - dealokuje miejsce w pamiêci dla wskazanego wêz³a
@ return: void
*/
void unsetNode(RBTNode *node);

/* findNode - Wyszukuje wêze³ o kluczu k
* k - klucz,
@ return: wskaŸnik do wêz³¹ zawieraj¹cego klucz o wartoœci k,
*/
RBTNode *findRBT(int k);

/* minRBT - szuka najmniejszego wêz³a
* node - korzeñ,
@ return: wskaŸnik do najmniejszego wêz³a
*/
RBTNode *minRBT(RBTNode *node);

/* succRBT - zwaraca nastêpnik node
* node - wêze³
@ return: wskaŸnik do wêz³a, który jest nastêpnikiem node
*/
RBTNode *succRBT(RBTNode *node);

/* rot_L - wykonuje rotacjê drzewa w lewo wzglêdem wêz³a node
* node - wêze³
@ return: void
*/
void rot_L(RBTNode *node);

/* rot_R - wykonuje rotacjê drzewa w prawo wzglêdem wêz³a node
* node - wêze³
@ return: void
*/
void rot_R(RBTNode *node);

/* insertRBT - wstawia nowy wêze³ o kluczu k do drzewa
* k - klucz,
@ return: void
*/
void insertRBT(int k);

/* removeRBT - usuwa wêze³ node z drzewa
* node - usuwany wêze³,
@ return: void
*/
void removeRBT(RBTNode *node);

/* DFSRelease - usuwa drzewo rekurencyjnie,
* node - korzeñ drzewa,
@ return: void
*/
void DFSRelease(RBTNode *node);

/* printRBT - wyœwietla drzewo w konsoli
* node - korzeñ drzewa,
@ return: void
*/
void printRBT(RBTNode *node);

#endif /* __RED_BLACK_TREE__ */