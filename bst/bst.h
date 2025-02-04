#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

typedef struct BST_NODE
{
    int chave;
    struct BST_NODE *node_esquerdo, *node_direito;

} *node;

node inserir(int numero, node raiz);
void preorder(node arvore);
void inorder(node arvore);
void posorder(node arvore);
void reverso(node arvore);
int altura(node arvore);
int qtdFolhas(node arvore);
void caminho(node arvore, int chave_procura);
node remover(int numero, node raiz);

#endif  // BST_H_INCLUDED