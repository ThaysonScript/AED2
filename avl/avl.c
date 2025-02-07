#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//função inserir recebe como parâmetro o ponteiro para a raiz de uma árvore,
//o valor a ser inserido e RETORNA o ponteiro para a (sub)árvore resultante
arvore inserir (arvore raiz, int valor, int *cresceu) {
	//caso base - instância mais simples do problema
	//inserir em uma árvore vazia
	if(raiz == NULL) {
		//1. Alocar espaço para o nó
		arvore novo = (arvore) malloc(sizeof(no));
		//2. Inicializar o nó
		novo->valor = valor;
		novo->esq = NULL;
		novo->dir = NULL;
        novo->fb = 0;   
        *cresceu = 1;
		//3. Ligação do novo nó com o restante da árvore
		return novo;	
	} else {
		if(valor > raiz->valor) {
			raiz->dir = inserir(raiz->dir, valor, cresceu);
            //atualizar o FB e rotacionar se necessário
            if(*cresceu) {
                switch(raiz->fb) {
                    case -1:
                        *cresceu = 0;
                        raiz->fb = 0;
                        break;
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0;
                        return rotacionar(raiz);
                        break;
                }
            }

		} else {
			raiz->esq = inserir(raiz->esq, valor, cresceu);	
            //atualizar o FB e rotacionar se necessário
            //nó 10 do desenho
            if(*cresceu) {
                switch(raiz->fb) {
                    case -1:
                        *cresceu = 0;
                        return rotacionar(raiz);
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 1;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                }  
            }

		}
		return raiz;
	}
}

arvore remover (arvore raiz, int valor, int *diminuiu) {
    if(raiz == NULL) {
        *diminuiu = 0;
        return NULL;    
    } else {
        //elemento encontrado
        if(valor == raiz->valor) {
            //caso 1: zero filhos - folhas
            if(raiz->esq  == NULL && raiz->dir == NULL ) {
                *diminuiu = 1;
                free(raiz);
                return NULL;                  
            } 
            
            //caso 2: um filho
            //a) exatamente um filho esquerdo
            if(raiz->esq != NULL && raiz->dir == NULL ) {
                *diminuiu = 1;
                arvore raizResultante = raiz->esq;
                free(raiz);
                return raizResultante;
            }

            // caso 2: um filho
            // b) exatamente um filho direito
            if(raiz->esq == NULL && raiz->dir != NULL ) {
                *diminuiu = 1;
                arvore raizResultante = raiz->dir;
                free(raiz);
                return raizResultante;
            }

            //caso 3: dois filhos
            if(raiz->esq  != NULL && raiz->dir != NULL) {
                arvore aux = maiorElemento(raiz->esq);
                raiz->valor = aux->valor;
                /* Remoção do predecessor (maior elemento da subárvore esquerda)
                   Esse procedimento é equivalente a uma remoção pela subárvore esquerda */
                raiz->esq = remover(raiz->esq, aux->valor, diminuiu);
                if (*diminuiu) {
                    // Atualiza fb conforme a remoção na subárvore esquerda
                    switch (raiz->fb) {
                        case 0:
                            raiz->fb = 1;
                            *diminuiu = 0;
                            break;
                        case 1:
                            *diminuiu = 1;
                            return rotacionar(raiz);
                        case -1:
                            raiz->fb = 0;
                            *diminuiu = 1;
                            break;
                    }
                }
                return raiz;                  
            }

        } else {
            //procurar pelo elemento
            if(valor > raiz->valor) {
			    raiz->dir = remover(raiz->dir, valor, diminuiu);
                //Atualizar FB e rotacionar se necessário
                if(*diminuiu) {
                    switch(raiz->fb) {
                        case 0:
                            raiz->fb = -1;
                            *diminuiu = 0;
                            break;
                        case 1:
                            raiz->fb = 0;
                            *diminuiu = 1;
                            break;
                        case -1:
                            *diminuiu = 1;
                            return rotacionar(raiz);
                            break;
                    }
                }
		    } else {
			    raiz->esq = remover(raiz->esq, valor, diminuiu);	
                if(*diminuiu) {
                    switch(raiz->fb) {
                        case 0:
                            raiz->fb = 1;
                            *diminuiu = 0;
                            break;
                        case 1:
                            *diminuiu = 1;
                            return rotacionar(raiz);
                            break;
                        case -1:
                            raiz->fb = 0;
                            *diminuiu = 1;
                            break;
                    }
                }
		    }
            return raiz ;
        }
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

int fator_balanceamento(arvore raiz) {
    if (raiz == NULL)
        return 0;
        
    return (altura(raiz->dir) - altura(raiz->esq));
}

/*
     p
    / \
   t1  u
      / \
     t2 t3

     u
    / \
   p   t3
  / \
 t1 t2

*/
arvore rotacao_simples_esquerda(arvore raiz) {
    arvore p, u, t1, t2, t3;
    //inicializar
    p = raiz;
    u = p->dir;
    t2 = u->esq;

    //Atualizar os ponteiros com o estado resultante
    u->esq = p;
    p->dir = t2;

    //Atualizar fatores de balanço
    if(u->fb == 0) {
        p->fb = 1;
        u->fb = -1;
    } else {
        p->fb = 0;
        u->fb = 0;

    }
    return u;  
}

arvore rotacao_dupla_esquerda(arvore raiz) {
    arvore p = raiz;
    arvore u = p->dir;
    arvore v = u->esq;
    arvore t2 = v->esq;
    arvore t3 = v->dir;
    
    p->dir = t2;
    u->esq = t3;
    v->esq = p;
    v->dir = u;
    
    if (v->fb == -1) {
        p->fb = 0;
        u->fb = 1;
        
    } else if (v->fb == 0) {
        p->fb = 0;
        u->fb = 0;

    } else {
        p->fb = -1;
        u->fb = 0;
    }
    
    v->fb = 0;
    return v;
}


arvore rotacao_simples_direita(arvore raiz) {
    arvore p = raiz;
    arvore u = p->esq;

    p->esq = u->dir;
    u->dir = p;

    if (u->fb == 0) {
        p->fb = -1;
        u->fb = 1;

    } else {
        p->fb = 0;
        u->fb = 0;
    }
    return u;
}


arvore rotacao_dupla_direita(arvore raiz) {
    arvore p = raiz;
    arvore u = p->esq;
    arvore v = u->dir;
    arvore t2 = v->esq;
    arvore t3 = v->dir;
    
    p->esq = t3;
    u->dir = t2;
    v->esq = u;
    v->dir = p;
    
    if (v->fb == 1) {
        p->fb = 0;
        u->fb = -1;

    } else if (v->fb == 0) {
        p->fb = 0;
        u->fb = 0;

    } else {
        p->fb = 1;
        u->fb = 0;
    }

    v->fb = 0;
    return v;
}


arvore rotacionar(arvore raiz){
    // subarvore esta desbalanceada ao lado direito. Rotacionar esta subarvore para esquerda
    if(raiz->fb > 0)
        // verifica se a subarvore direita esta desbalanceada ao lado direito
        if(raiz->dir->fb >= 0)
            return rotacao_simples_esquerda(raiz);      // rotacao simples basta

        // senao, a subarvore direita esta desbalanceada ao lado esquerdo, exigindo uma rotacao dupla
        else
            return rotacao_dupla_esquerda(raiz);        // rotacionar para direita e depois esquerda

    // subarvore esta desbalanceada ao lado esquerdo. Rotacionar esta subarvore para direita
    else
        // verifica se a subarvore esquerda esta desbalanceada ao lado esquerdo
        if(raiz->esq->fb <= 0)
            return rotacao_simples_direita(raiz);      // rotacao simples basta

        // senao, a subarvore esquerda esta desbalanceada ao lado direita, exigindo uma rotacao dupla
        else
            return rotacao_dupla_direita(raiz);         // rotacionar para esquerda e depois direita
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

void preorder(arvore raiz){
    if(raiz != NULL) {
        printf("[%d %d]", raiz->valor, raiz->fb);
        preorder(raiz->esq);
        preorder(raiz->dir);
    }
}