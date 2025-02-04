#ifndef BST_H
#define BST_H

typedef struct no {
	int valor;
	struct no *esq, *dir;
} no;

typedef no * arvore;

arvore inserir (arvore raiz, int valor);        // op 1

void preorder(arvore raiz);                     // op 2

void inorder(arvore raiz);                      // op 3

void posorder(arvore raiz);                     // op 4

void reverso(arvore raiz);                      // op 5

int altura(arvore raiz);                        // op 6

int qtdFolhas(arvore raiz);                     // op 7

void caminho(arvore raiz, int chave_procura);   // op 8

arvore remover (arvore raiz, int valor);        // op 9

arvore maiorElemento(arvore raiz);              // funcao utilidade

#endif