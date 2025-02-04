#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// inserir novo nó na arvore
node inserir(node raiz, int valor, int *cresceu)
{
    // caso base, se arvore vazia ou inserir novo nó folha
    if (raiz == NULL)
    {
        raiz = (node)malloc(sizeof(node));           // alocar um novo nó

        raiz->chave = valor;                         // adicionar o valor ao nó
        raiz->no_esquerdo = raiz->no_direito = NULL; // subarvores ou nó, como vazio
        raiz->fator_balanco = 0;                     // inicializar o fator de balanco
        *cresceu = 1;                                // inicializar a identificacao de crescimento
    }
    // inserir nó em subarvore esquerda
    else if (valor < raiz->chave)
    {
        raiz->no_esquerdo = inserir(raiz->no_esquerdo, valor, cresceu);
        if (*cresceu)
        {
            switch (raiz->fator_balanco)
            {
            case 1:
                raiz->fator_balanco = 0;
                *cresceu = 0;
                break;
            case 0:
                raiz->fator_balanco = -1;
                *cresceu = 1;
                break;
            case -1:
                raiz->fator_balanco = -2;
                raiz = rotacionar(raiz);
                *cresceu = 0;
                break;
            }
        }
    }
    // inserir nó em subarvore direita
    else
    {
        raiz->no_direito = inserir(raiz->no_direito, valor, cresceu);
        if (*cresceu)
        {
            switch (raiz->fator_balanco)
            {
            case -1:
                raiz->fator_balanco = 0;
                *cresceu = 0;
                break;
            case 0:
                raiz->fator_balanco = 1;
                *cresceu = 1;
                break;
            case 1:
                raiz->fator_balanco = 2;
                raiz = rotacionar(raiz);
                *cresceu = 0;
                break;
            }
        }
    }

    return raiz;
}

node remover(node raiz, int valor, int *diminuiu)
{
    if (raiz == NULL)
    {
        *diminuiu = 0;
        return NULL;
    }
    if (valor < raiz->chave)
    {
        raiz->no_esquerdo = remover(raiz->no_esquerdo, valor, diminuiu);
        if (*diminuiu)
        {
            switch (raiz->fator_balanco)
            {
            case -1:
                raiz->fator_balanco = 0;
                *diminuiu = 1;
                break;
            case 0:
                raiz->fator_balanco = 1;
                *diminuiu = 0;
                break;
            case 1:
                raiz->fator_balanco = 2;
                raiz = rotacionar(raiz);
                *diminuiu = 1;
                break;
            }
        }
    }
    else if (valor > raiz->chave)
    {
        raiz->no_direito = remover(raiz->no_direito, valor, diminuiu);
        if (*diminuiu)
        {
            switch (raiz->fator_balanco)
            {
            case 1:
                raiz->fator_balanco = 0;
                *diminuiu = 1;
                break;
            case 0:
                raiz->fator_balanco = -1;
                *diminuiu = 0;
                break;
            case -1:
                raiz->fator_balanco = -2;
                raiz = rotacionar(raiz);
                *diminuiu = 1;
                break;
            }
        }
    }
    else
    {
        if (raiz->no_esquerdo == NULL || raiz->no_direito == NULL)
        {
            node temp = (raiz->no_esquerdo != NULL) ? raiz->no_esquerdo : raiz->no_direito;
            free(raiz);
            *diminuiu = 1;
            return temp;
        }
        else
        {
            node temp = maiorElemento(raiz->no_esquerdo);
            raiz->chave = temp->chave;
            raiz->no_esquerdo = remover(raiz->no_esquerdo, temp->chave, diminuiu);
            if (*diminuiu)
            {
                switch (raiz->fator_balanco)
                {
                case -1:
                    raiz->fator_balanco = 0;
                    *diminuiu = 1;
                    break;
                case 0:
                    raiz->fator_balanco = 1;
                    *diminuiu = 0;
                    break;
                case 1:
                    raiz->fator_balanco = 2;
                    raiz = rotacionar(raiz);
                    *diminuiu = 1;
                    break;
                }
            }
        }
    }
    return raiz;
}

node rotacao_simples_esquerda(node p)
{
    node u = p->no_direito;
    p->no_direito = u->no_esquerdo;
    u->no_esquerdo = p;

    if (u->fator_balanco == 1)
    {
        p->fator_balanco = 0;
        u->fator_balanco = 0;
    }
    else if (u->fator_balanco == 0)
    {
        p->fator_balanco = 1;
        u->fator_balanco = -1;
    }
    return u;
}

node rotacao_simples_direita(node p)
{
    node u = p->no_esquerdo;
    p->no_esquerdo = u->no_direito;
    u->no_direito = p;

    if (u->fator_balanco == -1)
    {
        p->fator_balanco = 0;
        u->fator_balanco = 0;
    }
    else if (u->fator_balanco == 0)
    {
        p->fator_balanco = -1;
        u->fator_balanco = 1;
    }
    return u;
}

node rotacao_dupla_esquerda(node p)
{
    node u = p->no_direito;
    node v = u->no_esquerdo;

    u->no_esquerdo = v->no_direito;
    p->no_direito = v->no_esquerdo;
    v->no_esquerdo = p;
    v->no_direito = u;

    if (v->fator_balanco == 1)
    {
        p->fator_balanco = -1;
        u->fator_balanco = 0;
    }
    else if (v->fator_balanco == -1)
    {
        p->fator_balanco = 0;
        u->fator_balanco = 1;
    }
    else
    {
        p->fator_balanco = 0;
        u->fator_balanco = 0;
    }
    v->fator_balanco = 0;
    return v;
}

node rotacao_dupla_direita(node p)
{
    node u = p->no_esquerdo;
    node v = u->no_direito;

    u->no_direito = v->no_esquerdo;
    p->no_esquerdo = v->no_direito;
    v->no_esquerdo = u;
    v->no_direito = p;

    if (v->fator_balanco == -1)
    {
        p->fator_balanco = 1;
        u->fator_balanco = 0;
    }
    else if (v->fator_balanco == 1)
    {
        p->fator_balanco = 0;
        u->fator_balanco = -1;
    }
    else
    {
        p->fator_balanco = 0;
        u->fator_balanco = 0;
    }
    v->fator_balanco = 0;
    return v;
}

node rotacionar(node raiz)
{
    if (raiz->fator_balanco > 0)
    {
        if (raiz->no_direito->fator_balanco >= 0)
            return rotacao_simples_esquerda(raiz);
        else
            return rotacao_dupla_esquerda(raiz);
    }
    else
    {
        if (raiz->no_esquerdo->fator_balanco <= 0)
            return rotacao_simples_direita(raiz);
        else
            return rotacao_dupla_direita(raiz);
    }
}

node maiorElemento(node raiz)
{
    if (raiz == NULL)
        return NULL;
    while (raiz->no_direito != NULL)
        raiz = raiz->no_direito;
    return raiz;
}

void preorder(node raiz)
{
    if (raiz != NULL)
    {
        printf("[%d %d]", raiz->chave, raiz->fator_balanco);
        preorder(raiz->no_esquerdo);
        preorder(raiz->no_direito);
    }
}