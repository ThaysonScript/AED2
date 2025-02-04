#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

typedef struct avl_node
{
    int chave;
    int fator_balanco;
    struct avl_node *no_esquerdo;
    struct avl_node *no_direito;
} AVL_NODE;

typedef AVL_NODE *node;

node inserir(node raiz, int valor, int *cresceu);
node remover(node raiz, int valor, int *diminuiu);
node rotacao_simples_esquerda(node p);
node rotacao_simples_direita(node p);
node rotacao_dupla_esquerda(node p);
node rotacao_dupla_direita(node p);
node rotacionar(node raiz);
node maiorElemento(node raiz);
void preorder(node raiz);

#endif // AVL_H_INCLUDED