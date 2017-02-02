/***
* RedBlackTree.c - implementacja funkcji biblioteki RedBlackTree.h
*
* Copyright (c) Krzysztof Abram
*
****/

#include <stdlib.h>
#include "RedBlackTree.h"

RBTNode *root;
RBTNode *sentinelNode; // liœæ wartownik
char *cr, *cl, *cp;

/* initializeTree - inicjuje drzewo
* tree - wskaŸnik do drzewa
@ return: void
*/
void initializeTree(){
	// inicjacja wartownika:
	sentinelNode = newNode();
	sentinelNode->color = BLACK;
	sentinelNode->left = NULL;
	sentinelNode->right = NULL;
	sentinelNode->up = NULL;

	// inicjacja korzenia:
	root = newNode( );
	root->left = sentinelNode;
	root->right = sentinelNode;
	root->up = sentinelNode;
	return;
}// end initializeTree

/* initializeNode - inicjuje wêze³
* node - wskaŸnik do wêz³a
@ return: void
*/
void initializeNode(RBTNode *node){
	node->left = sentinelNode;
	node->right = sentinelNode;
	node->up = sentinelNode;
	node->color = RED;
	return;
}// end initializeNode

/* newNode - tworzy miejsce w pamiêci dla nowego wêz³a
@ return: wskaŸnik do pamiêci alokowanej dynamicznie
*/
RBTNode *newNode(void){
	RBTNode *node;
	if ( node = (RBTNode*)malloc(sizeof(RBTNode)) )
		return node;
	return NULL;
}// end newNode

/* unsetNode - dealokuje miejsce w pamiêci dla wskazanego wêz³a
@ return: void
*/
void unsetNode(RBTNode *node){
	if (node) free(node);
	return;
}// end unsetNode

/* findNode - Wyszukuje wêze³ o kluczu k
* k - klucz,
@ return: wskaŸnik do wêz³¹ zawieraj¹cego klucz o wartoœci k,
*/
RBTNode *findRBT(int k){
	RBTNode *node = root;
	while ((node != sentinelNode) && (node->key != k)){
		if (k < node->key) node = node->left;
		else node = node->right;
	}
	if (node == sentinelNode) return NULL;
	return node;
}// end findRBT

/* minRBT - szuka najmniejszego wêz³a
* node - korzeñ,
@ return: wskaŸnik do najmniejszego wêz³a
*/
RBTNode *minRBT(RBTNode *node){
	if (!node) return NULL;
	while (node->left != sentinelNode)
		node = node->left;
	return node;
}// end minRBT

/* succRBT - zwaraca nastêpnik node
* node - wêze³
@ return: wskaŸnik do wêz³a, który jest nastêpnikiem node
*/
RBTNode *succRBT(RBTNode *node){
	RBTNode *r;
	if (node != sentinelNode){
		if (node->right != sentinelNode) 
			return minRBT(node->right);
		else {
			r = node->up;
			while ((r != sentinelNode) && (node == r->right)){
				node = r;
				r = r->up;
			}
			return r;
		}
	}
	return sentinelNode;
}// end succRBT

/* rot_L - wykonuje rotacjê drzewa w lewo wzglêdem wêz³a node
* node - wêze³
@ return: void
*/
void rot_L(RBTNode *node){
	RBTNode *B, *p;

	B = node->right;
	if (B != sentinelNode){
		p = node->up;
		node->right = B->left;
		if (node->right != sentinelNode) 
			node->right->up = node;

		B->left = node;
		B->up = p;
		node->up = B;

		if (p != sentinelNode){
			if (p->left == node) p->left = B;
			else p->right = B;
		} else root = B;
	}
	return;
}// end rot_L

/* rot_R - wykonuje rotacjê drzewa w prawo wzglêdem wêz³a node
* node - wêze³
@ return: void
*/
void rot_R(RBTNode *node){
	RBTNode * B, *p;

	B = node->left;
	if (B != sentinelNode){
		p = node->up;
		node->left = B->right;
		if (node->left != sentinelNode) 
			node->left->up = node;

		B->right = node;
		B->up = p;
		node->up = B;

		if (p != sentinelNode){
			if (p->left == node) p->left = B; 
			else p->right = B;
		}
		else root = B;
	}
	return;
}// end rot_R

/* insertRBT - wstawia nowy wêze³ o kluczu k do drzewa
* k - klucz,
@ return: void
*/
void insertRBT(int k){
	RBTNode * X, *Y;

	X = newNode( );        // Tworzymy nowy wêze³
	initializeNode( X );
	X->up = root;
	X->key = k;
	if (X->up == sentinelNode) root = X; // X staje siê korzeniem
	else
		while (true){             // Szukamy liœcia do zast¹pienia przez X
			if (k < X->up->key){
				if (X->up->left == sentinelNode){
					X->up->left = X;  // X zastêpuje lewy liœæ
					break;
				}
				X->up = X->up->left;
			}
			else {
				if (X->up->right == sentinelNode){
					X->up->right = X; // X zastêpuje prawy liœæ
					break;
				}
				X->up = X->up->right;
			}
		}
	X->color = RED;         // Wêze³ kolorujemy na czerwono
	while ((X != root) && (X->up->color == RED)){
		if (X->up == X->up->up->left){
			Y = X->up->up->right; // Y -> wujek X

			if (Y->color == RED){  // Przypadek 1
				X->up->color = BLACK;
				Y->color = BLACK;
				X->up->up->color = RED;
				X = X->up->up;
				continue;
			}

			if (X == X->up->right){ // Przypadek 2
				X = X->up;
				rot_L(X);
			}

			X->up->color = BLACK; // Przypadek 3
			X->up->up->color = RED;
			rot_R(X->up->up);
			break;
		} else {                  // Przypadki lustrzane
			Y = X->up->up->left;

			if (Y->color == RED){ // Przypadek 1
				X->up->color = BLACK;
				Y->color = BLACK;
				X->up->up->color = RED;
				X = X->up->up;
				continue;
			}

			if (X == X->up->left){ // Przypadek 2
				X = X->up;
				rot_R(X);
			}

			X->up->color = BLACK; // Przypadek 3
			X->up->up->color = RED;
			rot_L(X->up->up);
			break;
		}
	}
	root->color = BLACK;
	return;
}// insertRBT

/* removeRBT - usuwa wêze³ node z drzewa
* node - usuwany wêze³,
@ return: void
*/
void removeRBT(RBTNode *node){
	RBTNode * W, *Y, *Z;

	if (node == NULL) return;
	if ((node->left == sentinelNode) || (node->right == sentinelNode)) Y = node;
	else Y = succRBT(node);

	if (Y->left != sentinelNode) Z = Y->left;
	else Z = Y->right;

	Z->up = Y->up;

	if (Y->up == sentinelNode) root = Z;
	else if (Y == Y->up->left) Y->up->left = Z;
	else Y->up->right = Z;

	if (Y != node) node->key = Y->key;

	if (Y->color == BLACK)   // Naprawa struktury drzewa czerwono-czarnego
		while ((Z != root) && (Z->color == BLACK))
			if (Z == Z->up->left){
				W = Z->up->right;

				if (W->color == RED){ // Przypadek 1
					W->color = BLACK;
					Z->up->color = RED;
					rot_L(Z->up);
					W = Z->up->right;
				}

				if ((W->left->color == BLACK) && (W->right->color == BLACK)){ // Przypadek 2
					W->color = RED;
					Z = Z->up;
					continue;
				}

				if (W->right->color == BLACK){ // Przypadek 3
					W->left->color = BLACK;
					W->color = RED;
					rot_R(W);
					W = Z->up->right;
				}

				W->color = Z->up->color; // Przypadek 4
				Z->up->color = BLACK;
				W->right->color = BLACK;
				rot_L(Z->up);
				Z = root;         // To spowoduje zakoñczenie pêtli
			}
			else { // Przypadki lustrzane
				W = Z->up->left;

				if (W->color == RED){  // Przypadek 1
					W->color = BLACK;
					Z->up->color = RED;
					rot_R(Z->up);
					W = Z->up->left;
				}

				if ((W->left->color == BLACK) && (W->right->color == BLACK)){ // Przypadek 2
					W->color = RED;
					Z = Z->up;
					continue;
				}

				if (W->left->color == BLACK){ // Przypadek 3
					W->right->color = BLACK;
					W->color = RED;
					rot_L(W);
					W = Z->up->left;
				}

				W->color = Z->up->color;  // Przypadek 4
				Z->up->color = BLACK;
				W->left->color = BLACK;
				rot_R(Z->up);
				Z = root;         // To spowoduje zakoñczenie pêtli
			}
	Z->color = BLACK;
	unsetNode(Y);
	return;
}// end removeRBT

/* DFSRelease - usuwa drzewo rekurencyjnie,
* node - korzeñ drzewa,
@ return: void
*/
void DFSRelease(RBTNode *node){
	if (node != sentinelNode){
		DFSRelease(node->left);   // usuwamy lewe poddrzewo
		DFSRelease(node->right);  // usuwamy prawe poddrzewo
		unsetNode(node);          // usuwamy sam wêze³
	}
	return;
}// end DFSRelease

char *substr(char *str, int pos, int len){
	int i, j;
	char s[1] = "";
	if (pos < 0 || len < 1) return s;
	char *sub = (char*)malloc((len+1)*sizeof(char));
	if (!sub) return s;
	for (i = pos, j = 0; i < (pos + len); i++, j++) 
		sub[j] = str[i];
	sub[j] = '\0';
	return sub;
}

/* printRBT - wyœwietla drzewo w konsoli
* sp -
* sn -
* node - korzeñ drzewa,
@ return: void
*/
static void _printRBT(char *sp, char *sn, RBTNode *node){
	char t[MAX_PRINT_LEN];
	char *sub = NULL;

	if (node != sentinelNode){
		strcpy(t, sp);
		if (strcmp(sn, cr) == 0) t[strlen(t) - 2] = ' ';
		_printRBT(strcat(t, cp), cr, node->right);

		sub = substr(t, 0, strlen(sp) - 2);
		strcpy(t, sub);
		printf("%s%s%c:%d\n", t, sn, node->color, node->key);

		strcpy(t, sp);
		if (strcmp(sn, cl) == 0) t[strlen(t) - 2] = ' ';
		_printRBT(strcat(t, cp), cl, node->left);
	}
	return;
}// end _printRBT

void printRBT(RBTNode *node){
	cr = (char*)malloc(2 * sizeof(char));
	cl = (char*)malloc(2 * sizeof(char));
	cp = (char*)malloc(2 * sizeof(char));
	char *sp = (char*)malloc(100 * sizeof(char));
	char *sn = (char*)malloc(100 * sizeof(char));
	if (!cr || !cl || !cp) return;
	strcpy(cr, "  ");
	strcpy(cl, "  ");
	strcpy(cp, "  ");
	strcpy(sp, "");
	strcpy(sn, "");
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	_printRBT(sp, sn, node);
	return;
}// end printRBT