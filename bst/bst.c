#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//função inserir recebe como parâmetro o ponteiro para a raiz de uma árvore,
//o valor a ser inserido e RETORNA o ponteiro para a (sub)árvore resultante
arvore inserir (arvore raiz, int valor) {
	//caso base - instância mais simples do problema
	//inserir em uma árvore vazia
	if(raiz == NULL) {
		//1. Alocar espaço para o nó
		arvore novo = (arvore) malloc(sizeof(no));
		//2. Inicializar o nó
		novo->valor = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		//3. Ligação do novo nó com o restante da árvore
		return novo;	
	} else {
		if(valor > raiz->valor) {
			raiz->dir = inserir(raiz->dir, valor);
		} else {
			raiz->esq = inserir(raiz->esq, valor);	
		}
		return raiz ;
	}
}

void preorder(arvore raiz){
    if(raiz != NULL) {
        printf("[%d]", raiz->valor);
        preorder(raiz->esq);
        preorder(raiz->dir);
    }
}

void inorder(arvore raiz){
    if(raiz != NULL) {
        inorder(raiz->esq);
        printf("[%d]", raiz->valor);
        inorder(raiz->dir);
    }
}

void posorder(arvore raiz){
    if(raiz != NULL) {
        posorder(raiz->esq);
        posorder(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}

void reverso(arvore raiz) {
    if (raiz != NULL) {
        reverso(raiz->dir);
        printf("[%d]", raiz->valor); 
        reverso(raiz->esq);
    }
}

int altura(arvore raiz) {
    if (raiz == NULL) {
        return 0;

    } else {
        int altura_esquerda = altura(raiz->esq);
        int altura_direita = altura(raiz->dir);

        return (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
    }
}

int qtdFolhas(arvore raiz) {
    if (raiz == NULL) 
        return 0;

    if (raiz->esq == NULL && raiz->dir == NULL) 
        return 1;

    return qtdFolhas(raiz->esq) + qtdFolhas(raiz->dir);
}

void caminho(arvore raiz, int chave_procura) {
    if (raiz == NULL) {
        printf("\n");

    } else {
        printf("[%d]", raiz->valor);

        (chave_procura > raiz->valor ? caminho(raiz->dir, chave_procura) : caminho(raiz->esq, chave_procura));

        // if(chave_procura > raiz->valor) {
        //     caminho(raiz->dir, chave_procura);

        // } else {
        //     caminho(raiz->esq, chave_procura);

        // }
    }
}

arvore remover (arvore raiz, int valor) {
    if(raiz == NULL) {
        return NULL;    
    } else {
        //elemento encontrado
        if(valor == raiz->valor) {
            //caso 1: zero filhos - folhas
            if(raiz->esq  == NULL && raiz->dir == NULL ) {
                free(raiz);
                return NULL;                  
            } 
            
            //caso 2: um filho
            //a) exatamente um filho esquerdo
            if(raiz->esq  != NULL && raiz->dir == NULL ) {
                arvore raizResultante = raiz->esq;
                free(raiz);
                return raizResultante;
            }

            //caso 2: um filho
            //b) exatamente um filho direito
            if(raiz->dir  != NULL && raiz->esq == NULL ) {
                arvore raizResultante = raiz->dir;
                free(raiz);
                return raizResultante;
            }

            //caso 3: dois filhos
            if(raiz->esq  != NULL && raiz->dir != NULL) {
                raiz->valor = maiorElemento(raiz->esq)->valor;
                raiz->esq = remover(raiz->esq, raiz->valor);        // verificar caso 1 e 2 novamente para a remocao
                return raiz;
                  
            }

        } else {
            //procurar pelo elemento
            if(valor > raiz->valor) {
			    raiz->dir = remover(raiz->dir, valor);
		    } else {
			    raiz->esq = remover(raiz->esq, valor);	
		    }
            return raiz;
        }
    }
}

arvore maiorElemento(arvore raiz){
    arvore temp = raiz;

    if(temp == NULL)
        return NULL;

    while(temp->dir != NULL) {
        temp = temp->dir;
    }
    return temp;
}