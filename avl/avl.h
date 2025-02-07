#ifndef BST_H
#define BST_H

typedef struct no {
    int fb;
    int valor;
    struct no *esq, *dir;
} no;

typedef no *arvore;

arvore inserir(arvore raiz, int valor, int *cresceu);

arvore remover(arvore raiz, int valor, int *diminuiu);

int fator_balanceamento(arvore raiz);

arvore maiorElemento(arvore raiz);

void preorder(arvore raiz);

arvore rotacionar(arvore raiz);

arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);

arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);

#endif