#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

node inserir(int numero, node raiz) {
    if (raiz == NULL) {
        raiz = (node) malloc(sizeof(node));

        raiz->chave = numero;
        raiz->node_esquerdo = NULL;
        raiz->node_direito = NULL;

    } else {
        if (numero > raiz->chave) {
            raiz->node_direito = inserir(numero, raiz->node_direito);

        } else {
            raiz->node_esquerdo = inserir(numero, raiz->node_esquerdo);
        }
    }

    return raiz;
}

void preorder(node arvore) {
    if(arvore != NULL) {
        printf("[%d]", arvore->chave);
        preorder(arvore->node_esquerdo);
        preorder(arvore->node_direito);
    }    
}

void inorder(node arvore) {
    if(arvore != NULL) {
        inorder(arvore->node_esquerdo);
        printf("[%d]", arvore->chave);
        inorder(arvore->node_direito);
    }
}

void posorder(node arvore) {
    if(arvore != NULL) {
        posorder(arvore->node_esquerdo);
        posorder(arvore->node_direito);
        printf("[%d]", arvore->chave);
    }
}

void reverso(node arvore) {
    if (arvore != NULL) {
        reverso(arvore->node_direito);
        printf("[%d]", arvore->chave); 
        reverso(arvore->node_esquerdo);
    }
}

int altura(node arvore) {
    if (arvore == NULL) {
        return -1;

    } else {
        int altura_esquerda = altura(arvore->node_esquerdo);
        int altura_direita = altura(arvore->node_direito);

        if (altura_esquerda > altura_direita) {
            return altura_esquerda + 1;

        } else {
            return altura_direita + 1;
        }
    }
}


int qtdFolhas(node arvore) {
    if (arvore == NULL) {
        return 0;

    } else if (arvore->node_esquerdo == NULL && arvore->node_direito == NULL) {
        return 1;
    }

    return qtdFolhas(arvore->node_esquerdo) + qtdFolhas(arvore->node_direito); 
}


void caminho(node arvore, int chave_procura) {
    if (arvore == NULL || chave_procura == arvore->chave) {
        printf("\n");

        return;
    }

    printf("[%d]", arvore->chave);

    if(chave_procura > arvore->chave) {
        caminho(arvore->node_direito, chave_procura);

    } else {
        caminho(arvore->node_esquerdo, chave_procura);

    }

}


node encontrarMinimo(node raiz) {
    while (raiz->node_esquerdo != NULL) {
        raiz = raiz->node_esquerdo;
    }
    return raiz;
}


node remover(int numero, node raiz) {
    if (raiz == NULL) {
        return raiz;
    }

    if (numero < raiz->chave) {
        raiz->node_esquerdo = remover(numero, raiz->node_esquerdo);

    } else if (numero > raiz->chave) {
        raiz->node_direito = remover(numero, raiz->node_direito);
    } else {
        // Caso 1: Nó sem filhos ou com apenas um filho
        if (raiz->node_esquerdo == NULL) {
            node temp = raiz->node_direito;
            free(raiz);
            return temp;

        } else if (raiz->node_direito == NULL) {
            node temp = raiz->node_esquerdo;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos
        node temp = encontrarMinimo(raiz->node_direito);
        raiz->chave = temp->chave;

        raiz->node_direito = remover(temp->chave, raiz->node_direito);
    }

    return raiz;
}